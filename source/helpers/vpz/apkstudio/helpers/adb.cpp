#include "adb.hpp"

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
    QStringList arguments;
    arguments << "-s";
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
        QRegularExpressionMatch matcher = regex.match(line);
        if (!matcher.hasMatch())
            continue;
        Application application;
        application.enabled = false;
        application.package = matcher.captured("package");
        application.path = matcher.captured("path");
        application.system = application.path.startsWith("/system");
        applications.append(application);
    }
    foreach (const QString &line, execute(enabled)) {
        QRegularExpressionMatch matcher = regex.match(line);
        if (!matcher.hasMatch())
            continue;
        Application application;
        application.enabled = true;
        application.package = matcher.captured("package");
        application.path = matcher.captured("path");
        application.system = application.path.startsWith("/system");
        applications.append(application);
    }
    return applications;
}

bool ADB::chmod(const QString &device, const QString &path, const QString &mode, bool recurse) const
{
    QStringList arguments;
    arguments << "-s";
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
    QStringList arguments;
    arguments << "-s";
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
    QRegularExpression emulator = QRegularExpression(REGEX_EMULATOR);
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
        if (emulator.match(device.serial).hasMatch())
            device.type = Device::EMULATOR;
        else
            device.type = Device::DEVICE;
        devices.append(device);
    }
    return devices;
}

bool ADB::enable(const QString &device, const QString &package, bool enable) const
{
    QStringList arguments;
    arguments << "-s";
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
    QStringList arguments;
    arguments << "-s";
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
    }
    arguments << "ls";
    arguments << "-l";
    arguments << path;
    QVector<File> files;
    QStringList lines = execute(arguments);
    QRegularExpression ls = QRegularExpression(REGEX_LS);
    foreach (const QString& line, lines) {
        QRegularExpressionMatch matcher = ls.match(line);
        if (!matcher.hasMatch())
            continue;
        File file;
        file.date = matcher.captured("date");
        file.group = matcher.captured("group");
        file.name = matcher.captured("name");
        file.owner = matcher.captured("owner");
        QString permission = matcher.captured("permission").trimmed();
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
        file.size = matcher.captured("size").toInt();
        file.time = matcher.captured("time");
        const QChar first = permission[0];
        if (first == '-')
            file.type = File::FILE;
        else if (first == 'b')
            file.type = File::BLOCK;
        else if (first == 'c')
            file.type = File::CHARACTER;
        else if (first == 'd')
            file.type = File::DIRECTORY;
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
                file.type = ((linked.length() == 1) ? ((linked.at(0) == "..") ? File::SYMLINK_DIRECTORY : File::SYMLINK_FILE) : File::SYMLINK_DIRECTORY);
            }
        }
        file.path.append(path);
        if (!file.path.endsWith('/'))
            file.path.append('/');
        if ((file.type == File::SYMLINK_DIRECTORY) || (file.type == File::SYMLINK_FILE)) {
            file.path.clear();
            file.path.append(file.link);
            file.link.prepend("-> ");
        } else
            file.path.append(file.name);
        files.append(file);
    }
    return files;
}

QString ADB::imei(const QString &device) const
{
    QStringList arguments;
    arguments << "-s";
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
    QStringList arguments;
    arguments << "-s";
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

QVector<Partition> ADB::partitions(const QString &device) const
{
    QStringList arguments;
    arguments << "-s";
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
    }
    arguments << "cat";
    arguments << "/proc/mounts";
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

QMap<QString, QString> ADB::properties(const QString &device) const
{
    QMap<QString, QString> properties;
    QStringList arguments;
    arguments << "-s";
    arguments << device;
    arguments << "shell";
    arguments << "getprop";
    QStringList lines = execute(arguments);
    QRegularExpression regex = QRegularExpression(REGEX_GETPROP);
    foreach (const QString &line, lines) {
        if (line.startsWith('#'))
            continue;
        QRegularExpressionMatch matcher = regex.match(line);
        if (!matcher.hasMatch())
            continue;
        QString key = matcher.captured(QString("key"));
        QString value = matcher.captured(QString("value"));
        properties.insert(key.trimmed(), value.trimmed());
    }
    return properties;
}

bool ADB::pull(const QString &device, const QString &source, const QString &destination) const
{
    QStringList arguments;
    arguments << "-s";
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
    QStringList arguments;
    arguments << "-s";
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
    QStringList arguments;
    arguments << "-s";
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
    QStringList arguments;
    QString mode = partition.flags.contains("rw") ? "ro" : "rw";
    arguments << "-s";
    arguments << device;
    arguments << "shell";
    if (Settings::rootShell()) {
        arguments << "su";
        arguments << "-c";
    }
    arguments << "mount";
    arguments << "-t";
    arguments << partition.fs;
    arguments << "-o";
    arguments << QString("remount,").append(mode);
    arguments << partition.device;
    arguments << partition.mount;
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
    QStringList arguments;
    arguments << "-s";
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
    QStringList arguments;
    arguments << "-s";
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
    execute(arguments, binary);
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
    QStringList arguments;
    arguments << "-s";
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

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
