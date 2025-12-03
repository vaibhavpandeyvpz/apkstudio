#include <QDebug>
#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProcess>
#include <QRegularExpression>
#include <QSettings>
#include <QStandardPaths>
#include <QThread>
#include <QUrl>
#include "tooldownloadworker.h"

#ifdef Q_OS_WIN
// Windows extraction handled via PowerShell or 7-Zip
#else
#include <sys/stat.h>
#endif

ToolDownloadWorker::ToolDownloadWorker(ToolType tool, QObject *parent)
    : QObject(parent), m_Tool(tool), m_NetworkManager(nullptr), m_NetworkReply(nullptr), m_DownloadFile(nullptr)
{
}

ToolDownloadWorker::~ToolDownloadWorker()
{
    abort();
}

void ToolDownloadWorker::abort()
{
    if (m_NetworkReply) {
        m_NetworkReply->abort();
        m_NetworkReply->deleteLater();
        m_NetworkReply = nullptr;
    }
    if (m_DownloadFile) {
        if (m_DownloadFile->isOpen()) {
            m_DownloadFile->close();
        }
        m_DownloadFile->deleteLater();
        m_DownloadFile = nullptr;
    }
    // Note: m_NetworkManager is a child of this, so it will be deleted automatically
}

void ToolDownloadWorker::download()
{
    emit started();
    
    QString downloadUrl = getDownloadUrl();
    if (downloadUrl.isEmpty()) {
        emit failed(tr("Could not determine download URL for this tool"));
        return;
    }

    emit progress(0, tr("Preparing download..."));

    // Create download directory
    QString downloadDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/apkstudio_downloads";
    QDir().mkpath(downloadDir);

    QString fileName = QUrl(downloadUrl).fileName();
    if (fileName.isEmpty()) {
        fileName = QString("tool_%1").arg(static_cast<int>(m_Tool));
    }
    QString filePath = downloadDir + "/" + fileName;

    emit progress(5, tr("Downloading %1...").arg(fileName));

    // Create network manager and file as member variables to keep them alive
    m_NetworkManager = new QNetworkAccessManager(this);
    m_DownloadFile = new QFile(filePath, this);
    
    if (!m_DownloadFile->open(QIODevice::WriteOnly)) {
        emit failed(tr("Could not create download file: %1").arg(m_DownloadFile->errorString()));
        m_DownloadFile->deleteLater();
        m_DownloadFile = nullptr;
        return;
    }

    // Download file
    QNetworkRequest request;
    request.setUrl(QUrl(downloadUrl));
    request.setRawHeader("User-Agent", "APK Studio");
    m_NetworkReply = m_NetworkManager->get(request);

    QObject::connect(m_NetworkReply, &QNetworkReply::downloadProgress, this, [this, fileName](qint64 bytesReceived, qint64 bytesTotal) {
        if (bytesTotal > 0) {
            int percentage = 5 + (bytesReceived * 70 / bytesTotal); // 5-75% for download
            double receivedMB = bytesReceived / 1024.0 / 1024.0;
            double totalMB = bytesTotal / 1024.0 / 1024.0;
            QString progressStr = tr("%1 MBs downloaded out of %2 MBs")
                .arg(receivedMB, 0, 'f', 2)
                .arg(totalMB, 0, 'f', 2);
            emit progress(percentage, progressStr);
        }
    }, Qt::QueuedConnection);

    QObject::connect(m_NetworkReply, &QNetworkReply::readyRead, this, [this]() {
        if (m_DownloadFile && m_DownloadFile->isOpen()) {
            m_DownloadFile->write(m_NetworkReply->readAll());
        }
    }, Qt::QueuedConnection);

    QObject::connect(m_NetworkReply, &QNetworkReply::finished, this, [this, filePath, fileName]() {
        if (!m_DownloadFile) {
            return;
        }
        
        m_DownloadFile->close();
        
        if (m_NetworkReply->error() != QNetworkReply::NoError) {
            m_DownloadFile->remove();
            emit failed(tr("Download failed: %1").arg(m_NetworkReply->errorString()));
            m_NetworkReply->deleteLater();
            m_NetworkReply = nullptr;
            m_DownloadFile->deleteLater();
            m_DownloadFile = nullptr;
            return;
        }

        // Write any remaining data
        if (m_NetworkReply->bytesAvailable() > 0) {
            m_DownloadFile->open(QIODevice::Append);
            m_DownloadFile->write(m_NetworkReply->readAll());
            m_DownloadFile->close();
        }

        // Extract or copy file to destination
        QString extractPath = getExtractPath();
        if (extractPath.isEmpty()) {
            m_DownloadFile->remove();
            emit failed(tr("Could not determine extraction path"));
            m_NetworkReply->deleteLater();
            m_NetworkReply = nullptr;
            m_DownloadFile->deleteLater();
            m_DownloadFile = nullptr;
            return;
        }

        QDir().mkpath(extractPath);

        bool extracted = false;
        if (fileName.endsWith(".zip", Qt::CaseInsensitive)) {
            emit progress(75, tr("Extracting %1...").arg(fileName));
            extracted = extractZip(filePath, extractPath);
        } else if (fileName.endsWith(".jar", Qt::CaseInsensitive)) {
            // JAR files don't need extraction, just copy to the extract path
            emit progress(75, tr("Copying %1...").arg(fileName));
            QString targetPath = QDir(extractPath).filePath(fileName);
            
            // Remove existing file if it exists
            if (QFile::exists(targetPath)) {
                QFile::remove(targetPath);
            }
            
            // Copy the JAR file
            if (QFile::copy(filePath, targetPath)) {
                extracted = true;
            } else {
                QString errorMsg = tr("Failed to copy JAR file to %1").arg(targetPath);
#ifdef QT_DEBUG
                qDebug() << errorMsg;
#endif
                emit failed(errorMsg);
                m_DownloadFile->remove();
                m_NetworkReply->deleteLater();
                m_NetworkReply = nullptr;
                m_DownloadFile->deleteLater();
                m_DownloadFile = nullptr;
                return;
            }
        } else if (fileName.endsWith(".tar.gz", Qt::CaseInsensitive) || fileName.endsWith(".tgz", Qt::CaseInsensitive)) {
            emit progress(75, tr("Extracting %1...").arg(fileName));
            extracted = extractTarGz(filePath, extractPath);
        } else if (fileName.endsWith(".pkg", Qt::CaseInsensitive)) {
            emit progress(75, tr("Installing %1...").arg(fileName));
            extracted = installPkg(filePath, extractPath);
        } else if (fileName.endsWith(".msi", Qt::CaseInsensitive)) {
            emit progress(75, tr("Installing %1...").arg(fileName));
            extracted = installMsi(filePath, extractPath);
        } else {
            emit progress(75, tr("Extracting %1...").arg(fileName));
            // Unknown file type, try to copy it
            QString targetPath = QDir(extractPath).filePath(fileName);
            if (QFile::exists(targetPath)) {
                QFile::remove(targetPath);
            }
            extracted = QFile::copy(filePath, targetPath);
        }

        if (!extracted) {
            QString errorMsg = tr("Failed to extract or copy downloaded file");
#ifdef QT_DEBUG
            qDebug() << errorMsg << "from" << filePath << "to" << extractPath;
#endif
            m_DownloadFile->remove();
            emit failed(errorMsg);
            m_NetworkReply->deleteLater();
            m_NetworkReply = nullptr;
            m_DownloadFile->deleteLater();
            m_DownloadFile = nullptr;
            return;
        }

        emit progress(90, tr("Locating executable..."));

        // Find executable
        QString executablePath = findExecutableInExtracted(extractPath);
        
        // For MSI/PKG installations, also check system locations
        if (executablePath.isEmpty() && (fileName.endsWith(".msi", Qt::CaseInsensitive) || fileName.endsWith(".pkg", Qt::CaseInsensitive))) {
            executablePath = findExecutableInSystemLocations();
        }
        
        if (executablePath.isEmpty()) {
            emit failed(tr("Could not find executable after installation"));
            m_NetworkReply->deleteLater();
            m_NetworkReply = nullptr;
            m_DownloadFile->deleteLater();
            m_DownloadFile = nullptr;
            return;
        }

        // Set executable permissions on Unix
        setExecutablePermissions(executablePath);

        // Save path to settings
        QSettings settings;
        switch (m_Tool) {
        case Java:
            settings.setValue("java_exe", executablePath);
            break;
        case Apktool:
            settings.setValue("apktool_jar", executablePath);
            break;
        case Jadx:
            settings.setValue("jadx_exe", executablePath);
            break;
        case Adb:
            settings.setValue("adb_exe", executablePath);
            break;
        case UberApkSigner:
            settings.setValue("uas_jar", executablePath);
            break;
        }
        settings.sync();

        // Clean up download file
        m_DownloadFile->remove();
        m_DownloadFile->deleteLater();
        m_DownloadFile = nullptr;

        emit progress(100, tr("Installation complete!"));
        emit finished(executablePath);
        m_NetworkReply->deleteLater();
        m_NetworkReply = nullptr;
    }, Qt::QueuedConnection);
}

QString ToolDownloadWorker::getDownloadUrl()
{
    QString platform;
#ifdef Q_OS_WIN
    platform = "windows";
#elif defined(Q_OS_MACOS)
    platform = "darwin";
#else
    platform = "linux";
#endif

    switch (m_Tool) {
    case Java:
    {
        // Microsoft OpenJDK platform-specific URLs
        if (platform == "darwin") {
            // macOS - use aarch64 (Apple Silicon) version
            // Note: For Intel Macs, you may need to provide x64 URL
            return "https://aka.ms/download-jdk/microsoft-jdk-11.0.29-macos-aarch64.pkg";
        } else if (platform == "linux") {
            // Linux - use aarch64 version
            // Note: For x86_64 systems, you may need to provide x64 URL
            return "https://aka.ms/download-jdk/microsoft-jdk-11.0.29-linux-aarch64.tar.gz";
        } else {
            // Windows
            return "https://aka.ms/download-jdk/microsoft-jdk-11.0.29-windows-x64.msi";
        }
    }
        
    case Apktool:
        return getLatestGitHubRelease("iBotPeaches/Apktool", "apktool.*\\.jar$");
        
    case Jadx:
    {
        QString url = getLatestGitHubRelease("skylot/jadx", QString("jadx-.*-%1\\.zip$").arg(platform));
        if (url.isEmpty()) {
            // Fallback to generic zip
            url = getLatestGitHubRelease("skylot/jadx", "jadx-.*\\.zip$");
        }
        return url;
    }
    
    case Adb:
    {
        if (platform == "darwin") {
            return "https://dl.google.com/android/repository/platform-tools-latest-darwin.zip";
        } else if (platform == "linux") {
            return "https://dl.google.com/android/repository/platform-tools-latest-linux.zip";
        } else {
            return "https://dl.google.com/android/repository/platform-tools-latest-windows.zip";
        }
    }
    
    case UberApkSigner:
        return getLatestGitHubRelease("patrickfav/uber-apk-signer", "uber-apk-signer.*\\.jar$");
    }
    
    return QString();
}

QString ToolDownloadWorker::getExtractPath()
{
    QString basePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (basePath.isEmpty()) {
        basePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.apkstudio";
    }
    
    QString toolName;
    switch (m_Tool) {
    case Java:
        toolName = "java";
        break;
    case Apktool:
        toolName = "apktool";
        break;
    case Jadx:
        toolName = "jadx";
        break;
    case Adb:
        toolName = "adb";
        break;
    case UberApkSigner:
        toolName = "uber-apk-signer";
        break;
    }
    
    return basePath + "/tools/" + toolName;
}

QString ToolDownloadWorker::findExecutableInExtracted(const QString &extractedPath)
{
    QDir dir(extractedPath);
    
    // Look for common executable names
    QStringList executableNames;
    switch (m_Tool) {
    case Java:
        // Java executable is typically in bin/ subdirectory
        executableNames << "bin/java" << "bin/java.exe" << "java" << "java.exe";
        // Also check for nested jdk directories
        {
            QDir dir(extractedPath);
            QStringList entries = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
            for (const QString &entry : entries) {
                if (entry.contains("jdk", Qt::CaseInsensitive) || entry.contains("java", Qt::CaseInsensitive)) {
                    executableNames << entry + "/bin/java" << entry + "/bin/java.exe";
                }
            }
        }
        break;
    case Apktool:
        // Look for any JAR file containing "apktool" in the name (handles versioned names like apktool_2.9.3.jar)
        {
            QDir dir(extractedPath);
            QStringList files = dir.entryList(QDir::Files, QDir::Name);
            for (const QString &file : files) {
                if (file.contains("apktool", Qt::CaseInsensitive) && file.endsWith(".jar", Qt::CaseInsensitive)) {
                    return dir.absoluteFilePath(file);
                }
            }
        }
        // Fallback to exact name (will be checked in the recursive search below)
        executableNames << "apktool.jar";
        break;
    case Jadx:
#ifdef Q_OS_WIN
        executableNames << "jadx/bin/jadx.bat" << "bin/jadx.bat";
#else
        executableNames << "jadx/bin/jadx" << "bin/jadx";
#endif
        break;
    case Adb:
        executableNames << "platform-tools/adb" << "adb/adb" << "adb";
#ifdef Q_OS_WIN
        executableNames << "platform-tools/adb.exe" << "adb/adb.exe" << "adb.exe";
#endif
        break;
    case UberApkSigner:
        // Look for any JAR file containing "uber-apk-signer" in the name (handles versioned names)
        {
            QDir dir(extractedPath);
            QStringList files = dir.entryList(QDir::Files, QDir::Name);
            for (const QString &file : files) {
                if (file.contains("uber-apk-signer", Qt::CaseInsensitive) && file.endsWith(".jar", Qt::CaseInsensitive)) {
                    return dir.absoluteFilePath(file);
                }
            }
        }
        // Fallback to exact name (will be checked in the recursive search below)
        executableNames << "uber-apk-signer.jar";
        break;
    }
    
    // Search recursively
    QStringList files = dir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
    for (const QString &file : files) {
        QString filePath = dir.absoluteFilePath(file);
        QFileInfo info(filePath);
        
        if (info.isDir()) {
            QString found = findExecutableInExtracted(filePath);
            if (!found.isEmpty()) {
                return found;
            }
        } else {
            for (const QString &exeName : executableNames) {
                if (info.fileName().compare(exeName, Qt::CaseInsensitive) == 0 ||
                    filePath.endsWith(exeName, Qt::CaseInsensitive)) {
                    return filePath;
                }
            }
            
            // For JAR files, check if filename matches pattern
            if (filePath.endsWith(".jar", Qt::CaseInsensitive)) {
                if ((m_Tool == Apktool && file.contains("apktool", Qt::CaseInsensitive)) ||
                    (m_Tool == UberApkSigner && file.contains("uber-apk-signer", Qt::CaseInsensitive))) {
                    return filePath;
                }
            }
        }
    }
    
    return QString();
}

QString ToolDownloadWorker::findExecutableInSystemLocations()
{
    // Search for installed executables in system locations (for MSI/PKG installations)
    QStringList searchPaths;
    
    switch (m_Tool) {
    case Java:
    {
#ifdef Q_OS_WIN
        // Windows: Check Program Files locations
        searchPaths << "C:/Program Files/Microsoft"
                    << "C:/Program Files (x86)/Microsoft"
                    << "C:/Program Files/Java"
                    << "C:/Program Files (x86)/Java";
#elif defined(Q_OS_MACOS)
        // macOS: Check Library locations
        searchPaths << "/Library/Java/JavaVirtualMachines"
                    << QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/Library/Java/JavaVirtualMachines";
#else
        // Linux: Check common locations
        searchPaths << "/usr/lib/jvm"
                    << "/opt/java"
                    << QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.local/share/java";
#endif
        break;
    }
    default:
        return QString(); // Only Java uses system locations for now
    }
    
    for (const QString &basePath : searchPaths) {
        QDir baseDir(basePath);
        if (!baseDir.exists()) {
            continue;
        }
        
        QStringList entries = baseDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (const QString &entry : entries) {
            if (entry.contains("jdk", Qt::CaseInsensitive) || entry.contains("java", Qt::CaseInsensitive)) {
                QString jdkPath = baseDir.absoluteFilePath(entry);
#ifdef Q_OS_WIN
                QString javaExe = jdkPath + "/bin/java.exe";
                if (QFile::exists(javaExe)) {
                    return javaExe;
                }
#elif defined(Q_OS_MACOS)
                QString javaExe = jdkPath + "/Contents/Home/bin/java";
                if (QFile::exists(javaExe)) {
                    return javaExe;
                }
#else
                QString javaExe = jdkPath + "/bin/java";
                if (QFile::exists(javaExe)) {
                    return javaExe;
                }
#endif
            }
        }
    }
    
    return QString();
}

bool ToolDownloadWorker::extractZip(const QString &zipPath, const QString &extractPath)
{
#ifdef Q_OS_WIN
    // Try PowerShell first (Windows 7+)
    QProcess process;
    QStringList args;
    args << "-Command" << QString("Expand-Archive -Path '%1' -DestinationPath '%2' -Force")
        .arg(zipPath).arg(extractPath);
    process.start("powershell", args);
    if (process.waitForFinished(120000)) { // 2 minute timeout
        if (process.exitCode() == 0) {
            return true;
        }
    }
    
    // Fallback: Try 7-Zip if available
    QStringList sevenZipPaths = {
        "C:/Program Files/7-Zip/7z.exe",
        "C:/Program Files (x86)/7-Zip/7z.exe"
    };
    for (const QString &sevenZip : sevenZipPaths) {
        if (QFile::exists(sevenZip)) {
            process.start(sevenZip, QStringList() << "x" << zipPath << QString("-o%1").arg(extractPath) << "-y");
            if (process.waitForFinished(120000) && process.exitCode() == 0) {
                return true;
            }
        }
    }
    
    return false;
#else
    // Use unzip command on Unix
    QProcess process;
    process.setWorkingDirectory(extractPath);
    process.start("unzip", QStringList() << "-q" << "-o" << zipPath);
    if (!process.waitForFinished(120000)) { // 2 minute timeout
        return false;
    }
    return process.exitCode() == 0;
#endif
}

bool ToolDownloadWorker::extractTarGz(const QString &tarPath, const QString &extractPath)
{
    // Use tar command (available on Unix systems)
    QProcess process;
    process.setWorkingDirectory(extractPath);
    process.start("tar", QStringList() << "-xzf" << tarPath);
    if (!process.waitForFinished(300000)) { // 5 minute timeout for large archives
        return false;
    }
    return process.exitCode() == 0;
}

bool ToolDownloadWorker::installPkg(const QString &pkgPath, const QString &installPath)
{
#ifdef Q_OS_MACOS
    // Perform headless installation of PKG file
    // For Java, wait for successful completion and verify installation
    
#ifdef QT_DEBUG
    qDebug() << "[installPkg] Starting PKG installation for tool:" << m_Tool;
    qDebug() << "[installPkg] PKG path:" << pkgPath;
    qDebug() << "[installPkg] Install path:" << installPath;
#endif
    
    // Verify PKG file exists and is readable
    QFileInfo pkgInfo(pkgPath);
    if (!pkgInfo.exists()) {
#ifdef QT_DEBUG
        qDebug() << "[installPkg] ERROR: PKG file does not exist:" << pkgPath;
#endif
        return false;
    }
    if (!pkgInfo.isReadable()) {
#ifdef QT_DEBUG
        qDebug() << "[installPkg] ERROR: PKG file is not readable:" << pkgPath;
#endif
        return false;
    }
#ifdef QT_DEBUG
    qDebug() << "[installPkg] PKG file exists, size:" << pkgInfo.size() << "bytes";
#endif
    
    QProcess process;
    int exitCode = 0;
    QString stdOut;
    QString stdErr;
    
    // For Java, we need admin privileges. Use osascript to elevate installer
    if (m_Tool == Java) {
#ifdef QT_DEBUG
        qDebug() << "[installPkg] Java installation requires admin privileges. Requesting elevation...";
#endif
        
        // Use osascript to run installer with admin privileges
        // Escape the pkg path for use in AppleScript
        QString escapedPkgPath = pkgPath;
        escapedPkgPath.replace("\\", "\\\\");
        escapedPkgPath.replace("\"", "\\\"");
        
        // Build the AppleScript command
        QString script = QString("do shell script \"installer -pkg \\\"%1\\\" -target / -verboseR\" with administrator privileges")
                            .arg(escapedPkgPath);
        
        QStringList args;
        args << "-e" << script;
        
#ifdef QT_DEBUG
        qDebug() << "[installPkg] Running osascript with elevation...";
        qDebug() << "[installPkg] AppleScript command:" << script;
#endif
        
        process.start("osascript", args);
    } else {
        // For other tools, try without elevation first
        QStringList args;
        args << "-pkg" << pkgPath;
        args << "-target" << "/";
        args << "-verboseR";
        
#ifdef QT_DEBUG
        qDebug() << "[installPkg] Running installer with args:" << args;
#endif
        process.start("installer", args);
    }
    
    if (!process.waitForStarted(30000)) {
#ifdef QT_DEBUG
        qDebug() << "[installPkg] Failed to start installer process";
#endif
        return false;
    }
    
#ifdef QT_DEBUG
    qDebug() << "[installPkg] Installer process started, waiting for completion...";
#endif
    
    // Wait for installation to complete (up to 10 minutes for Java)
    int timeout = (m_Tool == Java) ? 600000 : 300000; // 10 minutes for Java, 5 for others
    if (!process.waitForFinished(timeout)) {
#ifdef QT_DEBUG
        qDebug() << "[installPkg] Installer process timed out after" << (timeout / 1000) << "seconds";
#endif
        return false;
    }
    
    exitCode = process.exitCode();
    stdOut = QString::fromUtf8(process.readAllStandardOutput());
    stdErr = QString::fromUtf8(process.readAllStandardError());
    
#ifdef QT_DEBUG
    qDebug() << "[installPkg] Installer process finished with exit code:" << exitCode;
    if (!stdOut.isEmpty()) {
        qDebug() << "[installPkg] Installer stdout:" << stdOut;
    }
    if (!stdErr.isEmpty()) {
        qDebug() << "[installPkg] Installer stderr:" << stdErr;
    }
    
    // Check for common error messages
    if (exitCode != 0) {
        if (stdErr.contains("User canceled", Qt::CaseInsensitive) || stdOut.contains("User canceled", Qt::CaseInsensitive)) {
            qDebug() << "[installPkg] ERROR: User canceled the installation (admin password dialog was dismissed)";
        } else if (stdErr.contains("not authorized", Qt::CaseInsensitive) || stdOut.contains("not authorized", Qt::CaseInsensitive)) {
            qDebug() << "[installPkg] ERROR: Installation not authorized - admin privileges required";
        }
    }
#endif
    
    // For Java, verify successful installation by checking exit code and finding the executable
    if (m_Tool == Java) {
        if (exitCode != 0) {
#ifdef QT_DEBUG
            qDebug() << "[installPkg] Installer returned non-zero exit code, waiting 2 seconds and checking for files anyway...";
#endif
            // Installation failed, but wait a bit and check if files appeared anyway
            QThread::msleep(2000); // Wait 2 seconds for filesystem to catch up
        }
        
        // Search for installed Java in common locations
        QStringList searchPaths = {
            "/Library/Java/JavaVirtualMachines",
            QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/Library/Java/JavaVirtualMachines"
        };
        
#ifdef QT_DEBUG
        qDebug() << "[installPkg] Searching for Java in paths:" << searchPaths;
#endif
        
        // Retry search a few times in case filesystem is still updating
        for (int retry = 0; retry < 5; retry++) {
#ifdef QT_DEBUG
            qDebug() << "[installPkg] Search attempt" << (retry + 1) << "of 5";
#endif
            
            for (const QString &searchPath : searchPaths) {
                QDir dir(searchPath);
#ifdef QT_DEBUG
                qDebug() << "[installPkg] Checking path:" << searchPath << "exists:" << dir.exists();
#endif
                
                if (dir.exists()) {
                    QStringList entries = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
#ifdef QT_DEBUG
                    qDebug() << "[installPkg] Found" << entries.size() << "directories in" << searchPath;
#endif
                    
                    for (const QString &entry : entries) {
#ifdef QT_DEBUG
                        qDebug() << "[installPkg] Checking entry:" << entry;
#endif
                        
                        if (entry.contains("jdk", Qt::CaseInsensitive) || entry.contains("java", Qt::CaseInsensitive)) {
                            QString jdkPath = dir.absoluteFilePath(entry);
                            QString javaExe = jdkPath + "/Contents/Home/bin/java";
#ifdef QT_DEBUG
                            qDebug() << "[installPkg] Found JDK directory:" << jdkPath;
                            qDebug() << "[installPkg] Checking for Java executable at:" << javaExe;
#endif
                            
                            if (QFile::exists(javaExe)) {
                                // Found Java, verify it's executable
                                QFileInfo info(javaExe);
#ifdef QT_DEBUG
                                qDebug() << "[installPkg] Java executable found, isExecutable:" << info.isExecutable();
#endif
                                
                                if (info.isExecutable()) {
#ifdef QT_DEBUG
                                    qDebug() << "[installPkg] Java installation verified successfully at:" << javaExe;
#endif
                                    return true; // Successfully installed and found
                                }
                            } else {
#ifdef QT_DEBUG
                                qDebug() << "[installPkg] Java executable not found at:" << javaExe;
#endif
                            }
                        }
                    }
                }
            }
            
            if (retry < 4) {
#ifdef QT_DEBUG
                qDebug() << "[installPkg] Java not found, waiting 1 second before retry...";
#endif
                QThread::msleep(1000); // Wait 1 second before retry
            }
        }
        
        // Java not found after installation
#ifdef QT_DEBUG
        qDebug() << "[installPkg] Java installation failed - executable not found after all retries";
#endif
        return false;
    }
    
    // For other tools, just check exit code
    bool success = (exitCode == 0);
#ifdef QT_DEBUG
    qDebug() << "[installPkg] Installation result:" << (success ? "SUCCESS" : "FAILED");
#endif
    return success;
#else
    return false; // PKG files are macOS-only
#endif
}

bool ToolDownloadWorker::installMsi(const QString &msiPath, const QString &installPath)
{
#ifdef Q_OS_WIN
    // Perform headless installation of MSI file
    // For Java, wait for successful completion and verify installation
    
#ifdef QT_DEBUG
    qDebug() << "[installMsi] Starting MSI installation for tool:" << m_Tool;
    qDebug() << "[installMsi] MSI path:" << msiPath;
    qDebug() << "[installMsi] Install path:" << installPath;
#endif
    
    // Verify MSI file exists and is readable
    QFileInfo msiInfo(msiPath);
    if (!msiInfo.exists()) {
#ifdef QT_DEBUG
        qDebug() << "[installMsi] ERROR: MSI file does not exist:" << msiPath;
#endif
        return false;
    }
    if (!msiInfo.isReadable()) {
#ifdef QT_DEBUG
        qDebug() << "[installMsi] ERROR: MSI file is not readable:" << msiPath;
#endif
        return false;
    }
#ifdef QT_DEBUG
    qDebug() << "[installMsi] MSI file exists, size:" << msiInfo.size() << "bytes";
#endif
    
    QProcess process;
    
    // Use QDir::toNativeSeparators to ensure proper path format for Windows
    QString nativeMsiPath = QDir::toNativeSeparators(msiPath);
    
    // For Java, we need admin privileges. Use PowerShell to elevate msiexec
    if (m_Tool == Java) {
#ifdef QT_DEBUG
        qDebug() << "[installMsi] Java installation requires admin privileges. Requesting elevation...";
#endif
        
        // Build msiexec command with arguments
        QString msiexecCmd = QString("msiexec.exe /i \"%1\" /qn /norestart").arg(nativeMsiPath);
        
        // Use PowerShell to start msiexec with elevation (shows UAC prompt)
        // Start-Process with -Verb RunAs will show UAC dialog
        QStringList psArgs;
        psArgs << "-Command";
        psArgs << QString("Start-Process -FilePath 'msiexec.exe' -ArgumentList '/i', '%1', '/qn', '/norestart' -Verb RunAs -Wait -PassThru | ForEach-Object { exit $_.ExitCode }").arg(nativeMsiPath);
        
#ifdef QT_DEBUG
        qDebug() << "[installMsi] Running PowerShell with elevation...";
        qDebug() << "[installMsi] PowerShell command:" << psArgs;
#endif
        
        process.start("powershell.exe", psArgs);
    } else {
        // For other tools, try without elevation first
        QStringList args;
        args << "/i" << nativeMsiPath;
        args << "/qn"; // Quiet, no UI
        args << "/norestart"; // Don't restart
        
#ifdef QT_DEBUG
        qDebug() << "[installMsi] Running msiexec with args:" << args;
#endif
        process.start("msiexec", args);
    }
    
    if (!process.waitForStarted(30000)) {
#ifdef QT_DEBUG
        qDebug() << "[installMsi] Failed to start msiexec process";
#endif
        return false;
    }
    
#ifdef QT_DEBUG
    qDebug() << "[installMsi] msiexec process started, waiting for completion...";
#endif
    
    // Wait for installation to complete (up to 10 minutes for Java)
    int timeout = (m_Tool == Java) ? 600000 : 300000; // 10 minutes for Java, 5 for others
    if (!process.waitForFinished(timeout)) {
#ifdef QT_DEBUG
        qDebug() << "[installMsi] msiexec process timed out after" << (timeout / 1000) << "seconds";
#endif
        return false;
    }
    
    int exitCode = process.exitCode();
    QString stdOut = QString::fromUtf8(process.readAllStandardOutput());
    QString stdErr = QString::fromUtf8(process.readAllStandardError());
    
#ifdef QT_DEBUG
    qDebug() << "[installMsi] msiexec process finished with exit code:" << exitCode;
    if (!stdOut.isEmpty()) {
        qDebug() << "[installMsi] msiexec stdout:" << stdOut;
    }
    if (!stdErr.isEmpty()) {
        qDebug() << "[installMsi] msiexec stderr:" << stdErr;
    }
#endif
    
    // For Java, verify successful installation by checking exit code and finding the executable
    if (m_Tool == Java) {
        if (exitCode != 0) {
#ifdef QT_DEBUG
            qDebug() << "[installMsi] msiexec returned non-zero exit code (" << exitCode << ")";
            if (exitCode == 1925) {
                qDebug() << "[installMsi] ERROR: Exit code 1925 = Insufficient privileges. This MSI may require administrator rights.";
            } else if (exitCode == 1603) {
                qDebug() << "[installMsi] ERROR: Exit code 1603 = Fatal error during installation.";
            } else if (exitCode == 1619) {
                qDebug() << "[installMsi] ERROR: Exit code 1619 = Installation package could not be opened.";
            }
            qDebug() << "[installMsi] Waiting 2 seconds and checking for files anyway...";
#endif
            // Installation failed, but wait a bit and check if files appeared anyway
            QThread::msleep(2000); // Wait 2 seconds for filesystem to catch up
        }
        
        // Search for installed Java in default installation locations
        QStringList defaultPaths = {
            "C:/Program Files/Microsoft",
            "C:/Program Files (x86)/Microsoft",
            "C:/Program Files/Java",
            "C:/Program Files (x86)/Java"
        };
        
#ifdef QT_DEBUG
        qDebug() << "[installMsi] Searching for Java in paths:" << defaultPaths;
#endif
        
        // Retry search a few times in case filesystem is still updating
        for (int retry = 0; retry < 5; retry++) {
#ifdef QT_DEBUG
            qDebug() << "[installMsi] Search attempt" << (retry + 1) << "of 5";
#endif
            
            for (const QString &basePath : defaultPaths) {
                QDir baseDir(basePath);
#ifdef QT_DEBUG
                qDebug() << "[installMsi] Checking path:" << basePath << "exists:" << baseDir.exists();
#endif
                
                if (baseDir.exists()) {
                    QStringList entries = baseDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
#ifdef QT_DEBUG
                    qDebug() << "[installMsi] Found" << entries.size() << "directories in" << basePath;
#endif
                    
                    for (const QString &entry : entries) {
#ifdef QT_DEBUG
                        qDebug() << "[installMsi] Checking entry:" << entry;
#endif
                        
                        if (entry.contains("jdk", Qt::CaseInsensitive) || entry.contains("java", Qt::CaseInsensitive)) {
                            QString jdkPath = baseDir.absoluteFilePath(entry);
                            QString javaExe = jdkPath + "/bin/java.exe";
#ifdef QT_DEBUG
                            qDebug() << "[installMsi] Found JDK directory:" << jdkPath;
                            qDebug() << "[installMsi] Checking for Java executable at:" << javaExe;
#endif
                            
                            if (QFile::exists(javaExe)) {
                                // Found Java, verify it's a valid executable
                                QFileInfo info(javaExe);
#ifdef QT_DEBUG
                                qDebug() << "[installMsi] Java executable found, exists:" << info.exists() << "isFile:" << info.isFile();
#endif
                                
                                if (info.exists() && info.isFile()) {
#ifdef QT_DEBUG
                                    qDebug() << "[installMsi] Java installation verified successfully at:" << javaExe;
#endif
                                    return true; // Successfully installed and found
                                }
                            } else {
#ifdef QT_DEBUG
                                qDebug() << "[installMsi] Java executable not found at:" << javaExe;
#endif
                            }
                        }
                    }
                }
            }
            
            if (retry < 4) {
#ifdef QT_DEBUG
                qDebug() << "[installMsi] Java not found, waiting 1 second before retry...";
#endif
                QThread::msleep(1000); // Wait 1 second before retry
            }
        }
        
        // Java not found after installation
#ifdef QT_DEBUG
        qDebug() << "[installMsi] Java installation failed - executable not found after all retries";
        if (exitCode != 0) {
            qDebug() << "[installMsi] Installation failed with exit code:" << exitCode;
            if (exitCode == 1925) {
                qDebug() << "[installMsi] ERROR: This MSI installer requires administrator privileges.";
                qDebug() << "[installMsi] Please run APK Studio as administrator or install Java manually.";
            } else if (exitCode == 1603) {
                qDebug() << "[installMsi] ERROR: Fatal error during installation (exit code 1603).";
            } else if (exitCode == 1619) {
                qDebug() << "[installMsi] ERROR: Installation package could not be opened (exit code 1619).";
            }
        }
#endif
        return false;
    }
    
    // For other tools, check exit code
    bool success = (exitCode == 0);
#ifdef QT_DEBUG
    qDebug() << "[installMsi] Installation result:" << (success ? "SUCCESS" : "FAILED");
#endif
    return success;
#else
    return false; // MSI files are Windows-only
#endif
}

void ToolDownloadWorker::setExecutablePermissions(const QString &path)
{
#ifndef Q_OS_WIN
    QFile file(path);
    if (file.exists()) {
        QFile::Permissions perms = file.permissions();
        perms |= QFile::ExeUser | QFile::ExeGroup | QFile::ExeOther;
        file.setPermissions(perms);
    }
#endif
}

QString ToolDownloadWorker::getLatestGitHubRelease(const QString &repo, const QString &assetPattern)
{
    // Get latest release from GitHub API
    QString apiUrl = QString("https://api.github.com/repos/%1/releases/latest").arg(repo);
    
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setRawHeader("User-Agent", "APK Studio");
    QNetworkReply *reply = manager.get(request);
    
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    
    if (reply->error() != QNetworkReply::NoError) {
        reply->deleteLater();
        return QString();
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    reply->deleteLater();
    
    if (!doc.isObject()) {
        return QString();
    }
    
    QJsonObject obj = doc.object();
    QJsonArray assets = obj["assets"].toArray();
    
    QRegularExpression pattern(assetPattern, QRegularExpression::CaseInsensitiveOption);
    
    for (const QJsonValue &asset : assets) {
        QJsonObject assetObj = asset.toObject();
        QString name = assetObj["browser_download_url"].toString();
        if (pattern.match(name).hasMatch()) {
            return name;
        }
    }
    
    return QString();
}

