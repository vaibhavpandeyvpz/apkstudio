#ifndef VPZ_APKSTUDIO_RESOURCES_VARIANT_HPP
#define VPZ_APKSTUDIO_RESOURCES_VARIANT_HPP

#include <QRegularExpression>

namespace VPZ {
namespace APKStudio {
namespace Resources {

struct Highlight {
    QString regex;
    QString style;
};

struct Style {
    bool bold;
    QString color;
    bool italic;
    QString name;
    bool underline;
};

} // namespace Resources
} // namespace APKStudio
} // namespace VPZ

Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Highlight)
Q_DECLARE_METATYPE(VPZ::APKStudio::Resources::Style)

#endif // VPZ_APKSTUDIO_RESOURCES_VARIANT_HPP
