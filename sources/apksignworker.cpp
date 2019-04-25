#include <QDebug>
#include "apksignworker.h"
#include "processutils.h"

ApkSignWorker::ApkSignWorker(const QString &apk, const QString &keystore, const QString &keystorePassword, const QString &alias, const QString &aliasPassword, const bool zipalign, QObject *parent)
    : QObject(parent), m_Apk(apk), m_Keystore(keystore), m_KeystorePassword(keystorePassword), m_Alias(alias), m_AliasPassword(aliasPassword), m_Zipalign(zipalign)
{
}

void ApkSignWorker::sign()
{
    emit started();
#ifdef QT_DEBUG
    qDebug() << "Signing" << m_Apk;
#endif
    const QString java = ProcessUtils::javaExe();
    const QString uas = ProcessUtils::uberApkSignerJar();
    if (java.isEmpty() || uas.isEmpty()) {
        emit signFailed(m_Apk);
        return;
    }
    QString heap("-Xmx%1m");
    heap = heap.arg(QString::number(ProcessUtils::javaHeapSize()));
    QStringList args;
    args << heap << "-jar" << uas;
    args << "-a" << m_Apk << "--allowResign" << "--overwrite";
    if (!m_Keystore.isEmpty() && !m_Alias.isEmpty()) {
        args << "--ks" << m_Keystore;
        args << "--ksPass" << m_KeystorePassword;
        args << "--ksAlias" << m_Alias;
        args << "--ksKeyPass" << m_AliasPassword;
    }
    if (!m_Zipalign) {
        args << "--skipZipAlign";
    }
    ProcessResult result = ProcessUtils::runCommand(java, args);
#ifdef QT_DEBUG
    qDebug() << "Uber APK Signer returned code" << result.code;
#endif
    if (result.code != 0) {
        emit signFailed(m_Apk);
        return;
    }
    emit signFinished(m_Apk);
    emit finished();
}
