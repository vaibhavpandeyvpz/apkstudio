#ifndef VPZ_APKSTUDIO_HELPERS_ADB_HPP
#define VPZ_APKSTUDIO_HELPERS_ADB_HPP

#include "cli.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class ADB : public CLI
{
    Q_OBJECT
public:
    explicit ADB(const QString &, QObject * = 0);
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_ADB_HPP
