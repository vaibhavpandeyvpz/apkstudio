#include <QDir>
#include <QFile>
#include <QProcess>
#include <QProcessEnvironment>
#include <QRegularExpression>
#include <QSettings>
#include "processutils.h"

#define REGEXP_LF "[\\r\\n]"

QString ProcessUtils::apktoolJar()
{
    QSettings settings;
    const QString jar = settings.value("apktool_jar").toString();
    return (!jar.isEmpty() && QFile::exists(jar)) ? jar : QString();
}

QString ProcessUtils::javaExe()
{
    QSettings settings;
    QString exe;
    exe = settings.value("java_exe").toString();
    if (!exe.isEmpty()) {
        return exe;
    }
    QString jhome = QProcessEnvironment::systemEnvironment().value("JAVA_HOME");
    if (jhome.isEmpty()) {
        return QString();
    }
    exe = jhome.append(QDir::separator())
            .append("bin")
            .append(QDir::separator())
#ifdef Q_OS_WIN
            .append("java.exe");
#else
            .append("java");
#endif
    return QFile::exists(exe) ? exe : QString();
}

QString ProcessUtils::jadxExe()
{
    QSettings settings;
    const QString exe = settings.value("jadx_exe").toString();
    return (!exe.isEmpty() && QFile::exists(exe)) ? exe : QString();
}

ProcessResult ProcessUtils::runCommand(const QString &exe, const QStringList &args, int timeout)
{
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
        QRegularExpression crlf(REGEXP_LF);
        result.error = error.split(crlf, QString::SkipEmptyParts);
        result.output = output.split(crlf, QString::SkipEmptyParts);
    } else {
        result.code = -1;
    }
    return result;
}
