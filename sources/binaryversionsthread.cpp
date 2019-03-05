#include <QDebug>
#include <QRegularExpression>
#include "binaryversionsthread.h"
#include "processutils.h"

#define REGEXP_JAVA_VERSION "version \"(\\d+\\.\\d+\\.\\d+(_\\d+)?)\" "

BinaryVersionsThread::BinaryVersionsThread(QObject *parent)
    : QThread(parent)
{
}

void BinaryVersionsThread::run()
{
#ifdef QT_DEBUG
    qDebug() << "Using 'java' from" << ProcessUtils::javaExe();
#endif
    bool found = false;
    const QString java = ProcessUtils::javaExe();
    if (!java.isEmpty()) {
        ProcessResult result = ProcessUtils::runCommand(java, QStringList() << "-version");
#ifdef QT_DEBUG
        qDebug() << "Java returned code" << result.code;
#endif
        if (result.code == 0) {
#ifdef QT_DEBUG
            qDebug() << "Java returned" << result.output[0];
#endif
            QRegularExpression regexp(REGEXP_JAVA_VERSION);
            QRegularExpressionMatch match = regexp.match(result.output[0]);
            if (match.hasMatch()) {
                emit versionResolved("java", match.captured(1));
                found = true;
            }
        }
    }
    if (!found) {
        emit versionFailed("java");
        return;
    }
#ifdef QT_DEBUG
    qDebug() << "Using 'apktool' from" << ProcessUtils::apktoolJar();
#endif
    found = false;
    const QString apktool = ProcessUtils::apktoolJar();
    if (!apktool.isEmpty()) {
        QStringList args;
        args << "-jar";
        args << apktool;
        args << "--version";
        ProcessResult result = ProcessUtils::runCommand(java, args);
#ifdef QT_DEBUG
        qDebug() << "Apktool returned code" << result.code;
#endif
        if (result.code == 0) {
#ifdef QT_DEBUG
            qDebug() << "Apktool returned" << result.output[0];
#endif
            emit versionResolved("apktool", result.output[0].trimmed());
            found = true;
        }
    }
    if (!found) {
        emit versionFailed("apktool");
        return;
    }
#ifdef QT_DEBUG
    qDebug() << "Using 'jadx' from" << ProcessUtils::jadxExe();
#endif
    found = false;
    const QString jadx = ProcessUtils::jadxExe();
    if (!jadx.isEmpty()) {
        ProcessResult result = ProcessUtils::runCommand(jadx, QStringList() << "--version");
#ifdef QT_DEBUG
        qDebug() << "Jadx returned code" << result.code;
#endif
        if (result.code == 0) {
#ifdef QT_DEBUG
            qDebug() << "Jadx returned" << result.output[0];
#endif
            emit versionResolved("jadx", result.output[0].trimmed());
            found = true;
        }
    }
    if (!found) {
        emit versionFailed("jadx");
        return;
    }
    emit versionSuccess();
}
