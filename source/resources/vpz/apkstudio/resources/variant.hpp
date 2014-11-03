#ifndef VPZ_APKSTUDIO_RESOURCES_VARIANT_HPP
#define VPZ_APKSTUDIO_RESOURCES_VARIANT_HPP

#include <QHash>
#include <QStringList>

namespace VPZ {
namespace APKStudio {
namespace Resources {

struct Application {
    bool enabled;
    QString package;
    QString path;
    bool system;
};

struct Bracket {
    QChar character;
    int position;
};

struct Device {
    QString serial;
    enum Status {
        BOOTLOADER = 1,
        OFFLINE,
        ONLINE
    } status;
    enum Type {
        DEVICE = 1,
        EMULATOR
    } type;
};

struct File {
    QString date;
    QString group;
    QString link;
    QString name;
    QString owner;
    QString path;
    struct Permission {
        QString display;
        struct Group {
            bool execute;
            bool read;
            bool write;
        } group;
        struct Owner {
            bool execute;
            bool read;
            bool write;
        } owner;
        struct World {
            bool execute;
            bool read;
            bool write;
        } world;
    } permission;
    float size;
    QString time;
    enum Type {
        CHARACTER = 1,
        BLOCK,
        DIRECTORY,
        FILE,
        OTHER,
        PIPE,
        SOCKET,
        SYMLINK,
        SYMLINK_FILE,
        SYMLINK_DIRECTORY
    } type;
};

struct Photo {
    int height;
    QString name;
    QString path;
    long size;
    long time;
    int width;
};

struct Highlight {
    QString regex;
    QString style;
};

struct Music {
    int duration;
    QString name;
    QString path;
    long size;
    long time;
};

struct Partition {
    QStringList flags;
    QString fs;
    QString device;
    QString mount;
};

enum Reboot {
    BOOTLOADER,
    NORMAL,
    RECOVERY,
    SAFEMODE,
    SHUTDOWN,
    SOFT,
    ZYGOTE
};

struct Style {
    bool bold;
    QString color;
    bool italic;
    bool underline;
};

struct Video {
    int height;
    int duration;
    QString name;
    QString path;
    long time;
    int width;
};

typedef QHash<QString, Style> Theme;

} // namespace Resources
} // namespace APKStudio
} // namespace VPZ

Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Application)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Bracket)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Device)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::File)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Highlight)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Partition)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Reboot)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Style)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Theme)

#endif // VPZ_APKSTUDIO_RESOURCES_VARIANT_HPP
