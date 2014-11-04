#include "adb.hpp"
#include <QDebug>

using namespace VPZ::APKStudio::Resources;

namespace VPZ {
namespace APKStudio {
namespace Helpers {

ADB* ADB::self = nullptr;

ADB::ADB(QObject *parent) :
#ifdef Q_OS_WIN
    CLI(Settings::binary("adb.exe"), parent)
#else
    CLI(Settings::binary("adb"), parent)
#endif
{
}

QVector<Application> ADB::applications(const QString &device) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    arguments << "pm";
    arguments << "list";
    arguments << "packages";
    arguments << "-f";
    QStringList disabled(arguments);
    QStringList enabled(arguments);
    disabled << "-d";
    enabled << "-e";
    QVector<Application> applications;
    QRegularExpression regex = QRegularExpression(REGEX_APPLICATION);
    foreach (const QString &line, execute(disabled)) {
        QRegularExpressionMatch match = regex.match(line);
        if (!match.hasMatch())
            continue;
        Application application;
        application.enabled = false;
        application.package = match.captured("package");
        application.path = match.captured("path");
        application.name = application.path.section('/', -1, -1);
        application.system = application.path.startsWith("/system");
        applications.append(application);
    }
    foreach (const QString &line, execute(enabled)) {
        QRegularExpressionMatch match = regex.match(line);
        if (!match.hasMatch())
            continue;
        Application application;
        application.enabled = true;
        application.package = match.captured("package");
        application.path = match.captured("path");
        application.name = application.path.section('/', -1, -1);
        application.system = application.path.startsWith("/system");
        applications.append(application);
    }
    return applications;
}

bool ADB::chmod(const QString &device, const QString &path, const QString &mode, bool recurse) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
    }
    arguments << "chmod";
    if (recurse)
        arguments << "-R";
    arguments << mode;
    arguments << path;
    return execute(arguments).isEmpty();
}

bool ADB::create(const QString &device, const QString &path, bool directory) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
    }
    arguments << (directory ? "mkdir" : "touch");
    arguments << path;
    return execute(arguments).isEmpty();
}

QVector<Device> ADB::devices() const
{
    QVector<Device> devices;
    QRegularExpression regex = QRegularExpression(REGEX_EMULATOR);
    QStringList lines = execute(QStringList("devices"));
    foreach (const QString &line, lines) {
        QStringList parts = line.split("\t");
        if (parts.size() != 2)
            continue;
        Device device;
        device.serial = parts.at(0).trimmed();
        QString status = parts.at(1).trimmed();
        if (status == "bootloader")
            device.status = Device::BOOTLOADER;
        else if (status == "offline")
            device.status = Device::OFFLINE;
        else
            device.status = Device::ONLINE;
        if (regex.match(device.serial).hasMatch())
            device.type = Device::EMULATOR;
        else
            device.type = Device::DEVICE;
        devices.append(device);
    }
    return devices;
}

bool ADB::enable(const QString &device, const QString &package, bool enable) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
    }
    arguments << "pm";
    arguments << (enable ? "enable" : "disable");
    arguments << package;
    QStringList lines = execute(arguments);
    if (lines.size() != 1)
        return false;
    return (lines.first().trimmed() != "Killed");
}

QVector<File> ADB::files(const QString &device, const QString &path) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
        arguments << QString("ls -l \"%1\"").arg(path);
    } else {
        arguments << "ls";
        arguments << "-l";
        arguments << path;
    }
    QVector<File> files;
    QStringList lines = execute(arguments);
    QRegularExpression regex = QRegularExpression(REGEX_LS);
    foreach (const QString& line, lines) {
        QRegularExpressionMatch match = regex.match(line);
        if (!match.hasMatch())
            continue;
        File file;
        file.date = match.captured("date");
        file.group = match.captured("group");
        file.name = match.captured("name");
        file.owner = match.captured("owner");
        QString permission = match.captured("permission").trimmed();
        file.permission.display = permission;
        file.permission.owner.execute = (permission[3] == 'x');
        file.permission.owner.read = (permission[1] == 'r');
        file.permission.owner.write = (permission[2] == 'w');
        file.permission.group.execute = (permission[6] == 'x');
        file.permission.group.read = (permission[4] == 'r');
        file.permission.group.write = (permission[5] == 'w');
        file.permission.world.execute = (permission[9] == 'x');
        file.permission.world.read = (permission[7] == 'r');
        file.permission.world.write = (permission[8] == 'w');
        file.size = match.captured("size").toInt();
        file.time = match.captured("time");
        const QChar first = permission[0];
        if (first == '-')
            file.type = File::FILE;
        else if (first == 'b')
            file.type = File::BLOCK;
        else if (first == 'c')
            file.type = File::CHARACTER;
        else if (first == 'd')
            file.type = File::FOLDER;
        else if (first == 'l')
            file.type = File::SYMLINK;
        else if (first == 'p')
            file.type = File::PIPE;
        else if (first == 's')
            file.type = File::SOCKET;
        else
            file.type = File::OTHER;
        if (file.type == File::SYMLINK) {
            QStringList parts = file.name.split(QRegularExpression("\\s->\\s"));
            if (parts.count() == 2) {
                file.link = parts.at(1);
                file.name = parts.at(0);
                QStringList linked = file.link.split('/');
                file.type = ((linked.length() == 1) ? ((linked.at(0) == "..") ? File::SYMLINK_FOLDER : File::SYMLINK_FILE) : File::SYMLINK_FOLDER);
            }
        }
        file.path.append(path);
        if (!file.path.endsWith('/'))
            file.path.append('/');
        if ((file.type == File::SYMLINK_FOLDER) || (file.type == File::SYMLINK_FILE)) {
            file.path.clear();
            file.path.append(file.link);
            file.link.prepend("-> ");
        } else
            file.path.append(file.name);
        files.append(file);
    }
    return files;
}

QString ADB::IMEI(const QString &device) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    arguments << "dumpsys";
    arguments << "iphonesubinfo";
    QStringList lines = execute(arguments);
    QRegularExpression regex = QRegularExpression(REGEX_IMEI);
    foreach (const QString &line, lines) {
        if (!line.contains('='))
            continue;
        QStringList parts = line.split(regex);
        if (parts.at(0).trimmed() != "Device ID")
            continue;
        return parts.at(1).trimmed();
    }
    return QString();
}

bool ADB::install(const QString &device, const QString &apk) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "install";
    arguments << apk;
    QStringList lines = execute(arguments);
    foreach (const QString &line, lines) {
        if (line.startsWith("Success"))
            return true;
    }
    return false;
}

ADB *ADB::instance()
{
    if (!self)
        self = new ADB();
    return self;
}

void ADB::kill()
{
    execute(QStringList("kill-server"));
}

QVector<Music> ADB::music(const QString &device) const
{
    QVector<Music> musics;
    QStringList projection("duration");
    projection << "date_modified" << "_size" << "_data";
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    arguments << "content";
    arguments << "query";
    arguments << "--projection";
    arguments << projection.join(':');
    arguments << "--uri";
    QStringList files;
    files << execute(QStringList(arguments) << "content://media/external/audio/media/");
    files << execute(QStringList(arguments) << "content://media/internal/audio/media/");
    files.removeDuplicates();
    QRegularExpression regex = QRegularExpression(REGEX_PAIR);
    foreach (const QString &file, files) {
        QRegularExpressionMatchIterator iterator = regex.globalMatch(file);
        if (!iterator.hasNext())
            continue;
        Music music;
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            QString column = match.captured(1);
            QString value = match.captured(2);
            if (QString::compare("duration", column, Qt::CaseInsensitive) == 0)
                music.duration = value.toInt();
            else if (QString::compare("_size", column, Qt::CaseInsensitive) == 0)
                music.size = value.toLong();
            else if (QString::compare("date_modified", column, Qt::CaseInsensitive) == 0)
                music.time = value.toLong();
        }
        music.path = file.split("_data=").at(1).trimmed();
        if (music.path.startsWith("/data") || music.path.startsWith("/system"))
            continue;
        music.name = music.path.section('/', -1, -1);
        musics.append(music);
    }
    return musics;
}

QVector<Partition> ADB::partitions(const QString &device) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
        arguments << QString("cat /proc/mounts");
    } else {
        arguments << "cat";
        arguments << "/proc/mounts";
    }
    QVector<Partition> partitions;
    QStringList lines = execute(arguments);
    QRegularExpression whitespace = QRegularExpression("\\s+");
    foreach (const QString& line, lines) {
        QStringList parts = line.split(whitespace);
        if (parts.size() != 6)
            continue;
        Partition partition;
        partition.device = parts.at(0);
        partition.flags = parts.at(3).split(',');
        partition.mount = parts.at(1);
        partition.fs = parts.at(2);
        partitions.append(partition);
    }
    return partitions;
}

QVector<Photo> ADB::photos(const QString &device) const
{
    QVector<Photo> photos;
    QStringList projection("height");
    projection << "width" << "date_modified" << "_size" << "_data";
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    arguments << "content";
    arguments << "query";
    arguments << "--projection";
    arguments << projection.join(':');
    arguments << "--uri";
    QStringList files;
    files << execute(QStringList(arguments) << "content://media/external/images/media/");
    files << execute(QStringList(arguments) << "content://media/internal/images/media/");
    files.removeDuplicates();
    QRegularExpression regex = QRegularExpression(REGEX_PAIR);
    foreach (const QString &file, files) {
        QRegularExpressionMatchIterator iterator = regex.globalMatch(file);
        if (!iterator.hasNext())
            continue;
        Photo photo;
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            QString column = match.captured(1);
            QString value = match.captured(2);
            if (QString::compare("date_modified", column, Qt::CaseInsensitive) == 0)
                photo.time = value.toLong();
            else if (QString::compare("height", column, Qt::CaseInsensitive) == 0)
                photo.height = value.toInt();
            else if (QString::compare("_size", column, Qt::CaseInsensitive) == 0)
                photo.size = value.toLong();
            else if (QString::compare("width", column, Qt::CaseInsensitive) == 0)
                photo.width = value.toInt();
        }
        photo.path = file.split("_data=").at(1).trimmed();
        if (photo.path.startsWith("/data") || photo.path.startsWith("/system"))
            continue;
        photo.name = photo.path.section('/', -1, -1);
        photos.append(photo);
    }
    return photos;
}

QMap<QString, QString> ADB::properties(const QString &device) const
{
    QMap<QString, QString> properties;
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    arguments << "getprop";
    QStringList lines = execute(arguments);
    QRegularExpression regex = QRegularExpression(REGEX_GETPROP);
    foreach (const QString &line, lines) {
        if (line.startsWith('#'))
            continue;
        QRegularExpressionMatch match = regex.match(line);
        if (!match.hasMatch())
            continue;
        QString key = match.captured(QString("key"));
        QString value = match.captured(QString("value"));
        properties.insert(key.trimmed(), value.trimmed());
    }
    return properties;
}

bool ADB::pull(const QString &device, const QString &source, const QString &destination) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "pull";
    arguments << source;
    arguments << destination;
    QStringList lines = execute(arguments);
    foreach (const QString &line, lines) {
        if (line.endsWith("does not exist") || line.endsWith("Permission denied"))
            return false;
    }
    return true;
}

bool ADB::push(const QString &device, const QString &source, const QString &destination) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "pull";
    arguments << source;
    arguments << destination;
    QStringList lines = execute(arguments);
    foreach (const QString &line, lines) {
        if (line.startsWith("cannot stat") || line.startsWith("failed to copy"))
            return false;
    }
    return true;
}

void ADB::reboot(const QString &device, const Reboot &mode)
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
    }
    arguments << "reboot";
    switch (mode) {
    case NORMAL:
        break;
    case BOOTLOADER:
        arguments << "bootloader";
        break;
    case RECOVERY:
        arguments << "recovery";
        break;
    case SAFEMODE:
        arguments.removeLast();
        arguments << "setprop";
        arguments << "persist.sys.safemode";
        arguments << "1";
        execute(arguments);
        arguments.removeLast();
        arguments.removeLast();
        arguments << "ctl.restart";
        arguments << "zygote";
        break;
    case SHUTDOWN:
        arguments << "-p";
        break;
    case SOFT:
        arguments.removeLast();
        arguments << "killall";
        arguments << "system_server";
        break;
    case ZYGOTE:
        arguments.removeLast();
        arguments << "setprop";
        arguments << "ctl.restart";
        arguments << "zygote";
        break;
    }
    execute(arguments);
}

bool ADB::remount(const QString &device, const Partition &partition) const
{
    QString mode = partition.flags.contains("rw") ? "ro" : "rw";
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
        arguments << QString("mount -t %1 -o remount,%2 %3 %4").arg(partition.fs).arg(mode).arg(partition.device).arg(partition.mount);
    } else {
        arguments << "mount";
        arguments << "-t";
        arguments << partition.fs;
        arguments << "-o";
        arguments << QString("remount,").append(mode);
        arguments << partition.device;
        arguments << partition.mount;
    }
    execute(arguments);
    QVector<Partition> partitions = this->partitions(device);
    foreach (const Partition &newpartition, partitions) {
        if (partition.mount != newpartition.mount)
            continue;
        return newpartition.flags.contains(mode);
    }
    return false;
}

bool ADB::remove(const QString &device, const QString &path, bool recurse) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
    }
    arguments << "rm";
    if (recurse)
        arguments << "-R";
    arguments << path;
    return execute(arguments).isEmpty();
}

bool ADB::rename(const QString &device, const QString &source, const QString &destination) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
    }
    arguments << "mv";
    arguments << source;
    arguments << destination;
    return execute(arguments).isEmpty();
}

void ADB::screenshot(const QString &device, const QString &saveas)
{
    QString binary(Settings::javaHome());
#ifdef Q_OS_WIN
    binary.append("\\bin\\java.exe");
#else
    binary.append("/bin/java");
#endif
    QStringList arguments("-jar");
    arguments << Settings::binary("screenshot.jar");
    arguments << "-s";
    arguments << device;
    arguments << saveas;
    blockSignals(true);
    execute(arguments, binary);
    blockSignals(false);
}

void ADB::shell(const QString &device)
{
    QStringList arguments;
    QString binary;
#ifdef Q_OS_WIN
    binary.append("cmd.exe");
    arguments << "/c";
    arguments << Settings::binary("adb.exe");
#else
    binary.append("xterm");
    arguments << "-e";
    arguments << Settings::binary("adb");
#endif
    arguments << "-s";
    arguments << device;
    arguments << "shell";
    QProcess::startDetached(binary, arguments);
}

void ADB::start()
{
    execute(QStringList("start-server"));
}

bool ADB::uninstall(const QString &device, const QString &package) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
    }
    arguments << "pm";
    arguments << "uninstall";
    arguments << package;
    QStringList lines = execute(arguments);
    if (lines.size() != 1)
        return false;
    return (lines.first().trimmed() == "Success");
}

bool ADB::unmount(const QString &device, const Partition &partition) const
{
    QStringList arguments("-s");
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
        arguments << QString("umount %1").arg(partition.mount);
    } else {
        arguments << "umount";
        arguments << partition.mount;
    }
    execute(arguments);
    QVector<Partition> partitions = this->partitions(device);
    foreach (const Partition &newpartition, partitions) {
        if (QString::compare(partition.mount, newpartition.mount) == 0)
            return false;
    }
    return true;
}

QVector<Video> ADB::videos(const QString &device) const
{
    QVector<Video> videos;
    return videos;
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
