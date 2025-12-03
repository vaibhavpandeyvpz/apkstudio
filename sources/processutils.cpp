#include <QDebug>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QProcessEnvironment>
#include <QRegularExpression>
#include <QSettings>
#include "processutils.h"

#define REGEXP_CRLF "[\\r\\n]"

ProcessOutput* ProcessOutput::m_Self = nullptr;

void ProcessOutput::emitCommandFinished(const ProcessResult &result)
{
    emit commandFinished(result);
}

void ProcessOutput::emitCommandStarting(const QString &exe, const QStringList &args)
{
    emit commandStarting(exe, args);
}

ProcessOutput *ProcessOutput::instance()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    qRegisterMetaType<ProcessResult>("ProcessResult");
#else
    qRegisterMetaType<ProcessResult>();
#endif
    if (!m_Self) {
        m_Self = new ProcessOutput();
    }
    return m_Self;
}

QString ProcessUtils::adbExe()
{
    QSettings settings;
    QString exe = settings.value("adb_exe").toString();
    if (!exe.isEmpty() && QFile::exists(exe)) {
        return exe;
    }
    QString name("adb");
#ifdef Q_OS_WIN
    name.append(".exe");
#endif
    return findInPath(name);
}

QString ProcessUtils::apktoolJar()
{
    QSettings settings;
    const QString jar = settings.value("apktool_jar").toString();
    return (!jar.isEmpty() && QFile::exists(jar)) ? jar : QString();
}

QString ProcessUtils::findInPath(const QString &exe)
{
    auto result = runCommand(
#ifdef Q_OS_WIN
                "where",
#else
                "which",
#endif
                QStringList(exe));
    if ((result.code == 0) && (result.output.count() >= 1)) {
        auto location = result.output.first();
#ifdef QT_DEBUG
        qDebug() << exe << "found at" << location;
#endif
        return location;
    }
    return QString();
}

QString ProcessUtils::jadxExe()
{
    QSettings settings;
    QString exe = settings.value("jadx_exe").toString();
    return (!exe.isEmpty() && QFile::exists(exe)) ? exe : QString();
}

QString ProcessUtils::javaExe()
{
    QSettings settings;
    QString exe;
    exe = settings.value("java_exe").toString();
    if (!exe.isEmpty() && QFile::exists(exe)) {
        return exe;
    }
    QString name("java");
#ifdef Q_OS_WIN
    name.append(".exe");
#endif
    return findInPath(name);
}

int ProcessUtils::javaHeapSize()
{
    QSettings settings;
    return settings.value("java_heap", 256).toInt();
}

ProcessResult ProcessUtils::runCommand(const QString &exe, const QStringList &args, const int timeout)
{
#ifdef QT_DEBUG
    qDebug() << "Running" << exe << args;
#endif
    ProcessOutput::instance()->emitCommandStarting(exe, args);
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    
#ifdef Q_OS_WIN
    // On Windows, .bat and .cmd files need to be executed through cmd.exe
    QString actualExe = exe;
    QStringList actualArgs = args;
    QString workingDir;
    
    if (exe.endsWith(".bat", Qt::CaseInsensitive) || exe.endsWith(".cmd", Qt::CaseInsensitive)) {
        // Wrap .bat/.cmd files with cmd.exe /c
        // Syntax: cmd.exe /c "path\to\file.bat" arg1 arg2
        // Also set working directory to the batch file's directory so it can find relative paths
        QFileInfo fileInfo(exe);
        workingDir = fileInfo.absolutePath();
        actualExe = "cmd.exe";
        // Correct order: /c first, then batch file path, then arguments
        // QProcess will handle quoting automatically, so don't add quotes manually
        actualArgs.prepend(exe);  // Put the batch file path (QProcess handles quoting)
        actualArgs.prepend("/c"); // Then /c before the batch file
#ifdef QT_DEBUG
        qDebug() << "Wrapping .bat/.cmd file with cmd.exe:" << actualExe << actualArgs;
        qDebug() << "Setting working directory to:" << workingDir;
#endif
    }
    
    if (!workingDir.isEmpty()) {
        process.setWorkingDirectory(workingDir);
    }
    
    // Ensure Java is available in PATH for batch files that need it
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if (exe.endsWith(".bat", Qt::CaseInsensitive) || exe.endsWith(".cmd", Qt::CaseInsensitive)) {
        QString javaPath = ProcessUtils::javaExe(); // Get Java path from settings
        if (!javaPath.isEmpty()) {
            QFileInfo javaInfo(javaPath);
            QString javaHome = javaInfo.absolutePath();
            // Go up one level from bin to get JAVA_HOME
            if (javaHome.endsWith("/bin") || javaHome.endsWith("\\bin")) {
                QDir javaDir(javaHome);
                javaDir.cdUp();
                javaHome = javaDir.absolutePath();
            }
            env.insert("JAVA_HOME", javaHome);
            // Also add java.exe to PATH
            QString currentPath = env.value("PATH");
            QString javaBinPath = javaInfo.absolutePath();
            if (!currentPath.contains(javaBinPath, Qt::CaseInsensitive)) {
                env.insert("PATH", javaBinPath + ";" + currentPath);
            }
#ifdef QT_DEBUG
            qDebug() << "Setting JAVA_HOME to:" << javaHome;
            qDebug() << "Adding to PATH:" << javaBinPath;
#endif
        }
    }
    process.setProcessEnvironment(env);
    
    process.start(actualExe, actualArgs, QIODevice::ReadOnly);
#else
    process.start(exe, args, QIODevice::ReadOnly);
#endif
    
    ProcessResult result;
    if (process.waitForStarted(timeout * 1000)) {
        if (!process.waitForFinished(timeout * 1000)) {
            process.kill();
        }
        result.code = process.exitCode();
        QString error(process.readAllStandardError());
        QString output(process.readAllStandardOutput());
        QRegularExpression crlf(REGEXP_CRLF);
        result.error = error.split(crlf, Qt::SkipEmptyParts);
        result.output = output.split(crlf, Qt::SkipEmptyParts);
    } else {
        result.code = -1;
    }
    ProcessOutput::instance()->emitCommandFinished(result);
    return result;
}

QString ProcessUtils::uberApkSignerJar()
{
    QSettings settings;
    const QString jar = settings.value("uas_jar").toString();
    return (!jar.isEmpty() && QFile::exists(jar)) ? jar : QString();
}
