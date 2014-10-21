#ifndef VPZ_APKSTUDIO_RESOURCES_VARIANT_HPP
#define VPZ_APKSTUDIO_RESOURCES_VARIANT_HPP

#include <QHash>

namespace VPZ {
namespace APKStudio {
namespace Resources {

struct Bracket {
    QChar character;
    int position;
};

struct Highlight {
    QString regex;
    QString style;
};

struct Style {
    bool bold;
    QString color;
    bool italic;
    bool underline;
};

typedef QHash<QString, Style> Theme;

} // namespace Resources
} // namespace APKStudio
} // namespace VPZ

Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Bracket)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Highlight)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Style)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Theme)

#endif // VPZ_APKSTUDIO_RESOURCES_VARIANT_HPP
