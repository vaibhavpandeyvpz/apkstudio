#include <QDebug>
#include "apksignworker.h"
#include "processutils.h"

ApkSignWorker::ApkSignWorker(const QString &apk, const QString &keystore, const QString &keystorePassword, const QString &alias, const QString &aliasPassword, const bool zipalign, QObject *parent)
    : QObject(parent), m_Apk(apk), m_Keystore(keystore), m_KeystorePassword(keystorePassword), m_Alias(alias), m_AliasPassword(aliasPassword), m_Zipalign(zipalign)
{
}

void ApkSignWorker::sign()
{
#ifdef QT_DEBUG
    qDebug() << "Signing" << m_Apk;
#endif
    const QString java = ProcessUtils::javaExe();
    const QString uas = ProcessUtils::uberApkSignerJar();
    if (java.isEmpty() || uas.isEmpty()) {
        emit signFailed(m_Apk);
        return;
    }
    QStringList args;
    args << "-jar" << uas;
    args << "-a" << m_Apk;
    if (!m_Keystore.isEmpty() && !m_Alias.isEmpty()) {
        args << "--ks" << m_Keystore;
        args << "--ksPass" << m_KeystorePassword;
        args << "--ksAlias" << m_Alias;
        args << "--ksKeyPass" << m_AliasPassword;
    }
    if (!m_Zipalign) {
        args << "--skipZipAlign";
    }
    ProcessUtils::ProcessResult result = ProcessUtils::runCommand(java, args);
#ifdef QT_DEBUG
    qDebug() << "Uber APK Signer returned code" << result.code;
#endif
    if (result.code != 0) {
        emit signFailed(m_Apk);
        return;
    }
    emit signFinished(m_Apk);
}
