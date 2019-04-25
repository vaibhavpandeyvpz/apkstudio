#include <QDebug>
#include "apkdecompileworker.h"
#include "processutils.h"

ApkDecompileWorker::ApkDecompileWorker(const QString &apk, const QString &folder, const bool sources, QObject *parent)
    : QObject(parent), m_Apk(apk), m_Folder(folder), m_Sources(sources)
{
}

void ApkDecompileWorker::decompile()
{
    emit started();
#ifdef QT_DEBUG
    qDebug() << "Decompiling" << m_Apk << "into" << m_Folder;
#endif
    const QString java = ProcessUtils::javaExe();
    const QString apktool = ProcessUtils::apktoolJar();
    if (java.isEmpty() || apktool.isEmpty()) {
        emit decompileFailed(m_Apk);
        return;
    }
    emit decompileProgress(25, tr("Running apktool..."));
    QString heap("-Xmx%1m");
    heap = heap.arg(QString::number(ProcessUtils::javaHeapSize()));
    QStringList args;
    args << heap << "-jar" << apktool;
    args << "d" << "-o" << m_Folder << m_Apk;
    ProcessResult result = ProcessUtils::runCommand(java, args);
#ifdef QT_DEBUG
    qDebug() << "Apktool returned code" << result.code;
#endif
    if (result.code != 0) {
        emit decompileFailed(m_Apk);
        return;
    }
    if (m_Sources) {
        emit decompileProgress(75, tr("Running jadx..."));
        const QString jadx = ProcessUtils::jadxExe();
        if (jadx.isEmpty()) {
            emit decompileFailed(m_Apk);
            return;
        }
        args.clear();
        args << "-r" << "-d" << m_Folder << m_Apk;
        result = ProcessUtils::runCommand(jadx, args, PROCESS_TIMEOUT_SECS);
#ifdef QT_DEBUG
        qDebug() << "Jadx returned code" << result.code;
#endif
    }
    emit decompileFinished(m_Apk, m_Folder);
    emit finished();
}
