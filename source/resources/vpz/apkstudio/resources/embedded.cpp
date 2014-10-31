#include "embedded.hpp"

namespace VPZ {
namespace APKStudio {
namespace Resources {

QIcon Embedded::icon(const QString &name)
{
    return QIcon(QString(RESOURCE_PATH_ICON).append(name).append(".png"));
}

} // namespace Resources
} // namespace APKStudio
} // namespace VPZ

QIcon icon(const QString &name)
{
    return VPZ::APKStudio::Resources::Embedded::icon(name);
}
