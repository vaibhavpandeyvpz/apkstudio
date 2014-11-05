#include "variant.hpp"

QDataStream &operator <<(QDataStream &stream, const VPZ::APKStudio::Resources::File &file)
{
    stream << file.date;
    stream << file.group;
    stream << file.link;
    stream << file.name;
    stream << file.owner;
    stream << file.path;
    stream << file.permission.display;
    stream << file.permission.group.execute;
    stream << file.permission.group.read;
    stream << file.permission.group.write;
    stream << file.permission.owner.execute;
    stream << file.permission.owner.read;
    stream << file.permission.owner.write;
    stream << file.permission.world.execute;
    stream << file.permission.world.read;
    stream << file.permission.world.write;
    stream << file.size;
    stream << file.time;
    stream << file.type;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, VPZ::APKStudio::Resources::File &file)
{
    stream >> file.date;
    stream >> file.group;
    stream >> file.link;
    stream >> file.name;
    stream >> file.owner;
    stream >> file.path;
    stream >> file.permission.display;
    stream >> file.permission.group.execute;
    stream >> file.permission.group.read;
    stream >> file.permission.group.write;
    stream >> file.permission.owner.execute;
    stream >> file.permission.owner.read;
    stream >> file.permission.owner.write;
    stream >> file.permission.world.execute;
    stream >> file.permission.world.read;
    stream >> file.permission.world.write;
    stream >> file.size;
    stream >> file.time;
    int type;
    stream >> type;
    file.type = static_cast<VPZ::APKStudio::Resources::File::Type>(type);
    return stream;
}
