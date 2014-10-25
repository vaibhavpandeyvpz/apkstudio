#include "adb.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

ADB::ADB(const QString &executable, QObject *parent) :
    CLI(executable, parent)
{
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
