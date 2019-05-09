#include <QDebug>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QProcessEnvironment>
#include <QRegularExpression>
#include <QSettings>
#include <QTextCodec>
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
    qRegisterMetaType<ProcessResult>("ProcessResult");
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
    process.start(exe, args, QIODevice::ReadOnly);
    ProcessResult result;
    if (process.waitForStarted(timeout * 1000)) {
        if (!process.waitForFinished(timeout * 1000)) {
            process.kill();
        }
        result.code = process.exitCode();
        QString error(process.readAllStandardError());
        QString output(process.readAllStandardOutput());
        QRegularExpression crlf(REGEXP_CRLF);
        result.error = error.split(crlf, QString::SkipEmptyParts);
        result.output = output.split(crlf, QString::SkipEmptyParts);
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
