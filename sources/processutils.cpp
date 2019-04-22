#include <QDebug>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QProcessEnvironment>
#include <QRegularExpression>
#include <QSettings>
#include <QTextCodec>
#include "processutils.h"

#define REGEXP_LF "[\\r\\n]"

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
    exe = findInPath(name);
    if (!exe.isEmpty()) {
        return exe;
    }
    return QString();
}

QString ProcessUtils::apktoolJar()
{
    QSettings settings;
    const QString jar = settings.value("apktool_jar").toString();
    return (!jar.isEmpty() && QFile::exists(jar)) ? jar : QString();
}

QString ProcessUtils::expandEnvVar(const QString &name)
{
    QString value = QProcessEnvironment::systemEnvironment().value(name);
    if (value.isEmpty()) {
        return QString();
    }
#ifdef Q_OS_WIN
    QRegularExpression regexp("(%([^%]+)%)");
#else
    QRegularExpression regexp("(\\$([a-zA-Z0-9_]+))");
#endif
    if (!value.contains(regexp)) {
        return value;
    }
    QRegularExpressionMatchIterator matches = regexp.globalMatch(value);
    while (matches.hasNext()) {
        QRegularExpressionMatch match = matches.next();
        value.replace(match.capturedStart(1), match.capturedLength(1), expandEnvVar(match.captured(2)));
    }
    return value;
}

QString ProcessUtils::findInPath(const QString &exe)
{
    const QString path = expandEnvVar("PATH");
#ifdef QT_DEBUG
    qDebug() << "PATH is" << path;
#endif
    if (path.isEmpty()) {
        return QString();
    }
#ifdef Q_OS_WIN
    const char separator = ';';
#else
    const char separator = ':';
#endif
    const QStringList locations = path.split(separator);
    foreach (QString location, locations) {
        QDir dir(location);
        if (dir.exists() && dir.exists(exe)) {
#ifdef QT_DEBUG
            qDebug() << exe << "found in" << location;
#endif
            return QDir::toNativeSeparators(dir.filePath(exe));
        }
    }
    return QString();
}

QString ProcessUtils::jadxExe()
{
    QSettings settings;
    QString exe = settings.value("jadx_exe").toString();
    if (!exe.isEmpty() && QFile::exists(exe)) {
        return exe;
    }
    QString name("jadx");
#ifdef Q_OS_WIN
    name.append(".bat");
#endif
    exe = findInPath(name);
    if (!exe.isEmpty()) {
        return exe;
    }
    return QString();
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
    exe = findInPath(name);
    if (!exe.isEmpty()) {
        return exe;
    }
    QString jhome = expandEnvVar("JAVA_HOME");
    if (jhome.isEmpty()) {
        return QString();
    }
#ifdef QT_DEBUG
    qDebug() << "JAVA_HOME is" << jhome;
#endif
    exe = jhome.append(QDir::separator())
            .append("bin")
            .append(QDir::separator())
            .append(name);
    return QFile::exists(exe) ? exe : QString();
}

ProcessResult ProcessUtils::runCommand(const QString &exe, const QStringList &args, const int timeout)
{
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
        QRegularExpression crlf(REGEXP_LF);
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
