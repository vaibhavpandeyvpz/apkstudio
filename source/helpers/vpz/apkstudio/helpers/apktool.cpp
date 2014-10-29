#include "apktool.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

apktool* apktool::self = nullptr;

apktool::apktool(QObject *parent) :
#ifdef Q_OS_WIN
    CLI(QString(Settings::javaHome()).append("\\bin\\java.exe"), parent)
#else
    CLI(QString(Settings::javaHome()).append("/bin/java"), parent)
#endif
{
}

bool apktool::align(const QFileInfo &apk)
{
    if (!apk.exists() || !apk.isDir() || (QString::compare(apk.suffix(), "apk", Qt::CaseInsensitive) != 0))
        return false;
    QFileInfo aligned(QString(apk.absoluteDir().absolutePath()).append("signed_").append(apk.fileName()));
    QStringList arguments;
    arguments << "-f";
    arguments << "-v";
    arguments << QString::number(4);
    arguments << apk.absoluteFilePath();
    arguments << aligned.absoluteFilePath();
#ifdef Q_OS_WIN
    execute(arguments, Settings::binary("zipalign.exe"));
#else
    execute(arguments, Settings::binary("zipalign"));
#endif
    return aligned.exists() && aligned.isFile();
}

bool apktool::decompile(const QFileInfo &apk, const QFileInfo &folder, const QString &tag)
{
    if (!apk.exists() || !apk.isFile() || folder.exists() || (QString::compare(apk.suffix(), "apk", Qt::CaseInsensitive) != 0))
        return false;
    QStringList arguments;
    arguments << QString("-Xms").append(QString::number(Settings::heapSize())).append("m");
    arguments << "-jar";
    arguments << Settings::binary("apktool.jar");
    arguments << "--force";
    if (!tag.isEmpty()) {
        arguments << "--frame-path";
        arguments << Settings::frameworkPath();
        arguments << "--frame-tag";
        arguments << tag;
    }
    arguments << "--verbose";
    arguments << "--output";
    arguments << folder.absolutePath();
    arguments << "d";
    arguments << apk.absoluteFilePath();
    execute(arguments);
    QFileInfo yml(QString(folder.absolutePath()).append("/apktool.yml"));
    return yml.exists() && yml.isFile();
}

bool apktool::install(const QFileInfo &framework, const QString &tag)
{
    if (!framework.exists() || !framework.isFile() || tag.isEmpty())
        return false;
    QStringList arguments;
    arguments << QString("-Xms").append(QString::number(Settings::heapSize())).append("m");
    arguments << "-jar";
    arguments << Settings::binary("apktool.jar");
    arguments << "--force";
    arguments << "--frame-path";
    arguments << Settings::frameworkPath();
    arguments << "--frame-tag";
    arguments << tag;
    arguments << "--verbose";
    arguments << "if";
    arguments << framework.absoluteFilePath();
    QStringList lines = execute(arguments);
    foreach (const QString &line, lines) {
        if (!line.startsWith("INFO: Framework installed to:"))
            continue;
        QFileInfo file(line.section(':', 2).trimmed());
        if (!file.exists() || !file.isFile())
            continue;
        return true;
    }
    return false;
}

apktool *apktool::instance()
{
    if (!self)
        self = new apktool();
    return self;
}

bool apktool::recompile(const QFileInfo &folder, const QFileInfo &apk)
{
    if (!folder.exists() || !folder.isDir() || (QString::compare(apk.suffix(), "apk", Qt::CaseInsensitive) != 0))
        return false;
    if (apk.exists())
        QFile::remove(apk.absoluteFilePath());
    QStringList arguments;
    arguments << QString("-Xms").append(QString::number(Settings::heapSize())).append("m");
    arguments << "-jar";
    arguments << Settings::binary("apktool.jar");
    arguments << "--force";
    arguments << "--verbose";
    arguments << "--output";
    arguments << apk.absoluteFilePath();
    arguments << "b";
    arguments << folder.absolutePath();
    execute(arguments);
    return apk.exists() && apk.isFile();
}

bool apktool::sign(const QFileInfo &apk)
{
    if (!apk.exists() || !apk.isDir() || (QString::compare(apk.suffix(), "apk", Qt::CaseInsensitive) != 0))
        return false;
    QFileInfo _signed(QString(apk.absoluteDir().absolutePath()).append("signed_").append(apk.fileName()));
    QStringList arguments;
    arguments << QString("-Xms").append(QString::number(Settings::heapSize())).append("m");
    arguments << "-jar";
    arguments << Settings::binary("signapk.jar");
    arguments << "-w";
    arguments << Settings::signingCertificate();
    arguments << Settings::signingKey();
    arguments << apk.absoluteFilePath();
    arguments << _signed.absoluteFilePath();
    execute(arguments);
    return _signed.exists() && _signed.isFile();
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
