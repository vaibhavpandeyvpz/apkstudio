#include <QDebug>
#include <QRegularExpression>
#include "versionresolveworker.h"
#include "processutils.h"

#define REGEXP_ADB_VERSION "version (\\d+\\.\\d+\\.\\d+)$"
#define REGEXP_JAVA_VERSION "version \"([\\d._]+)\""
#define REGEXP_UAS_VERSION "Version: (\\d+\\.\\d+\\.\\d+)$"

VersionResolveWorker::VersionResolveWorker(QObject *parent)
    : QObject(parent)
{
}

void VersionResolveWorker::resolve()
{
    emit started();
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
        emit versionResolved("java", QString());
    }
#ifdef QT_DEBUG
    qDebug() << "Using 'apktool' from" << ProcessUtils::apktoolJar();
#endif
    found = false;
    const QString apktool = ProcessUtils::apktoolJar();
    if (!java.isEmpty() && !apktool.isEmpty()) {
        QStringList args;
        args << "-jar" << apktool;
        args << "--version";
        ProcessResult result = ProcessUtils::runCommand(java, args);
#ifdef QT_DEBUG
        qDebug() << "Apktool returned code" << result.code;
#endif
        if ((result.code == 0) && !result.output.isEmpty()) {
#ifdef QT_DEBUG
            qDebug() << "Apktool returned" << result.output.first();
#endif
            emit versionResolved("apktool", result.output.first().trimmed());
            found = true;
        }
    }
    if (!found) {
        emit versionResolved("apktool", QString());
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
        if ((result.code == 0) && !result.output.isEmpty()) {
#ifdef QT_DEBUG
            qDebug() << "Jadx returned" << result.output.first();
#endif
            emit versionResolved("jadx", result.output.first().trimmed());
            found = true;
        }
    }
    if (!found) {
        emit versionResolved("jadx", QString());
    }
#ifdef QT_DEBUG
    qDebug() << "Using 'adb' from" << ProcessUtils::adbExe();
#endif
    found = false;
    const QString adb = ProcessUtils::adbExe();
    if (!adb.isEmpty()) {
        ProcessResult result = ProcessUtils::runCommand(adb, QStringList() << "--version");
#ifdef QT_DEBUG
        qDebug() << "ADB returned code" << result.code;
#endif
        if ((result.code == 0) && !result.output.isEmpty()) {
#ifdef QT_DEBUG
            qDebug() << "ADB returned" << result.output.first();
#endif
            QRegularExpression regexp(REGEXP_ADB_VERSION);
            QRegularExpressionMatch match = regexp.match(result.output.first());
            if (match.hasMatch()) {
                emit versionResolved("adb", match.captured(1));
                found = true;
            }
        }
    }
    if (!found) {
        emit versionResolved("adb", QString());
    }
#ifdef QT_DEBUG
    qDebug() << "Using 'uas' from" << ProcessUtils::uberApkSignerJar();
#endif
    found = false;
    const QString uas = ProcessUtils::uberApkSignerJar();
    if (!java.isEmpty() && !uas.isEmpty()) {
        QStringList args;
        args << "-jar" << uas;
        args << "--version";
        ProcessResult result = ProcessUtils::runCommand(java, args);
#ifdef QT_DEBUG
        qDebug() << "Uber APK signer returned code" << result.code;
#endif
        if ((result.code == 0) && !result.output.isEmpty()) {
#ifdef QT_DEBUG
            qDebug() << "Uber APK signer returned" << result.output.first();
#endif
            QRegularExpression regexp(REGEXP_UAS_VERSION);
            QRegularExpressionMatch match = regexp.match(result.output.first());
            if (match.hasMatch()) {
                emit versionResolved("uas", match.captured(1));
                found = true;
            }
        }
        if (!found) {
            emit versionResolved("uas", QString());
        }
    }
    emit finished();
}
