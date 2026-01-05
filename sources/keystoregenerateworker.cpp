#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include "keystoregenerateworker.h"
#include "processutils.h"

KeystoreGenerateWorker::KeystoreGenerateWorker(const QString &keystorePath,
                                               const QString &keystorePassword,
                                               const QString &alias,
                                               const QString &aliasPassword,
                                               int validity,
                                               const QString &keyAlgorithm,
                                               int keySize,
                                               QObject *parent)
    : QObject(parent),
      m_KeystorePath(keystorePath),
      m_KeystorePassword(keystorePassword),
      m_Alias(alias),
      m_AliasPassword(aliasPassword),
      m_Validity(validity),
      m_KeyAlgorithm(keyAlgorithm),
      m_KeySize(keySize)
{
}

void KeystoreGenerateWorker::generate()
{
    emit started();
#ifdef QT_DEBUG
    qDebug() << "Generating keystore at" << m_KeystorePath;
#endif
    
    // Get Java executable
    const QString java = ProcessUtils::javaExe();
    if (java.isEmpty()) {
        emit generateFailed(tr("Java executable not found. Please configure Java in Settings."));
        emit finished();
        return;
    }
    
    // Find keytool (should be in the same directory as java)
    QFileInfo javaInfo(java);
    QString keytoolPath = javaInfo.absolutePath();
#ifdef Q_OS_WIN
    keytoolPath += "/keytool.exe";
#else
    keytoolPath += "/keytool";
#endif
    
    QFileInfo keytoolInfo(keytoolPath);
    if (!keytoolInfo.exists()) {
        emit generateFailed(tr("keytool not found at %1. Please ensure JDK is properly installed.").arg(keytoolPath));
        emit finished();
        return;
    }
    
    emit generateProgress(25, tr("Generating keystore..."));
    
    // Ensure the directory exists
    QFileInfo keystoreInfo(m_KeystorePath);
    QDir keystoreDir = keystoreInfo.absoluteDir();
    if (!keystoreDir.exists()) {
        if (!keystoreDir.mkpath(".")) {
            emit generateFailed(tr("Failed to create directory for keystore: %1").arg(keystoreDir.absolutePath()));
            emit finished();
            return;
        }
    }
    
    // Build keytool command
    // keytool -genkeypair -v -keystore <keystore> -alias <alias> -keyalg <algorithm> -keysize <size> -validity <days> -storepass <password> -keypass <password>
    QStringList args;
    args << "-genkeypair";
    args << "-v";
    args << "-keystore" << m_KeystorePath;
    args << "-alias" << m_Alias;
    args << "-keyalg" << m_KeyAlgorithm;
    args << "-keysize" << QString::number(m_KeySize);
    args << "-validity" << QString::number(m_Validity);
    args << "-storepass" << m_KeystorePassword;
    args << "-keypass" << m_AliasPassword;
    
    // Add default certificate information (required by keytool)
    // Using -dname to provide all required fields non-interactively
    QString dname = QString("CN=APK Studio, OU=Development, O=APK Studio, L=Unknown, ST=Unknown, C=US");
    args << "-dname" << dname;
    
    // Run keytool
    ProcessResult result = ProcessUtils::runCommand(keytoolPath, args, 60); // 60 second timeout for keytool
    
#ifdef QT_DEBUG
    qDebug() << "keytool returned code" << result.code;
    if (result.code != 0) {
        qDebug() << "keytool error output:" << result.error;
    }
#endif
    
    if (result.code != 0) {
        QString errorMsg = tr("Failed to generate keystore.");
        if (!result.error.isEmpty()) {
            errorMsg += "\n" + result.error.join("\n");
        }
        emit generateFailed(errorMsg);
        emit finished();
        return;
    }
    
    // Verify keystore was created
    keystoreInfo.refresh();
    if (!keystoreInfo.exists()) {
        emit generateFailed(tr("Keystore file was not created."));
        emit finished();
        return;
    }
    
    emit generateProgress(100, tr("Keystore generated successfully."));
    emit generateFinished(m_KeystorePath);
    emit finished();
}

