#include <QDebug>
#include "apkrecompileworker.h"
#include "processutils.h"

ApkRecompileWorker::ApkRecompileWorker(const QString &folder, QObject *parent)
    : QObject(parent), m_Folder(folder)
{
}

void ApkRecompileWorker::recompile()
{
#ifdef QT_DEBUG
    qDebug() << "Recompiling" << m_Folder;
#endif
    const QString java = ProcessUtils::javaExe();
    const QString apktool = ProcessUtils::apktoolJar();
    if (java.isEmpty() || apktool.isEmpty()) {
        emit recompileFailed(m_Folder);
        return;
    }
    QStringList args;
    args << "-jar" << apktool;
    args << "b" << m_Folder;
    ProcessResult result = ProcessUtils::runCommand(java, args);
#ifdef QT_DEBUG
    qDebug() << "Apktool returned code" << result.code;
#endif
    if (result.code != 0) {
        emit recompileFailed(m_Folder);
        return;
    }
    emit recompileFinished(m_Folder);
}
