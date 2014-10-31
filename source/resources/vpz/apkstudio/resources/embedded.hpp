#ifndef VPZ_APKSTUDIO_RESOURCES_EMBEDDED_HPP
#define VPZ_APKSTUDIO_RESOURCES_EMBEDDED_HPP

#include <QIcon>
#include "constant.hpp"

namespace VPZ {
namespace APKStudio {
namespace Resources {

class Embedded
{
public:
    static QIcon icon(const QString &);
};

} // namespace Resources
} // namespace APKStudio
} // namespace VPZ

QIcon icon(const QString &);

#endif // VPZ_APKSTUDIO_RESOURCES_EMBEDDED_HPP
