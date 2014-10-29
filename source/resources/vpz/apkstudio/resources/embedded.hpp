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
    static QIcon icon(const char *);
};

} // namespace Resources
} // namespace APKStudio
} // namespace VPZ

QIcon icon(const char *);

#endif // VPZ_APKSTUDIO_RESOURCES_EMBEDDED_HPP
