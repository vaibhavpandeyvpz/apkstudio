#include <QDebug>
#include "apkrecompileworker.h"
#include "processutils.h"

ApkRecompileWorker::ApkRecompileWorker(const QString &folder, bool aapt2, QObject *parent)
    : QObject(parent), m_Aapt2(aapt2), m_Folder(folder)
{
}

void ApkRecompileWorker::recompile()
{
    emit started();
#ifdef QT_DEBUG
    qDebug() << "Recompiling" << m_Folder;
#endif
    const QString java = ProcessUtils::javaExe();
    const QString apktool = ProcessUtils::apktoolJar();
    if (java.isEmpty() || apktool.isEmpty()) {
        emit recompileFailed(m_Folder);
        return;
    }
    QString heap("-Xmx%1m");
    heap = heap.arg(QString::number(ProcessUtils::javaHeapSize()));
    QStringList args;
    args << heap << "-jar" << apktool;
    args << "b" << m_Folder;
    // Apktool 2.12.1+ uses aapt2 by default, so we only need to specify --use-aapt1 if aapt1 is requested
    if (!m_Aapt2) {
        args << "--use-aapt1";
    }
    ProcessResult result = ProcessUtils::runCommand(java, args);
#ifdef QT_DEBUG
    qDebug() << "Apktool returned code" << result.code;
#endif
    if (result.code != 0) {
        emit recompileFailed(m_Folder);
        return;
    }
    emit recompileFinished(m_Folder);
    emit finished();
}
