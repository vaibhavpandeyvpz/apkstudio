#include <QDebug>
#include "adbinstallworker.h"
#include "processutils.h"

AdbInstallWorker::AdbInstallWorker(const QString &apk, QObject *parent)
    : QObject(parent), m_Apk(apk)
{
}

void AdbInstallWorker::install()
{
#ifdef QT_DEBUG
    qDebug() << "Installing" << m_Apk;
#endif
    const QString adb = ProcessUtils::adbExe();
    if (adb.isEmpty()) {
        emit installFailed(m_Apk);
        return;
    }
    QStringList args;
    args << "install" << m_Apk;
    ProcessResult result = ProcessUtils::runCommand(adb, args);
#ifdef QT_DEBUG
    qDebug() << "ADB returned code" << result.code;
#endif
    if (result.code != 0) {
        emit installFailed(m_Apk);
        return;
    }
    emit installFinished(m_Apk);
}
