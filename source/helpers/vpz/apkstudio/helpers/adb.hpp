#ifndef VPZ_APKSTUDIO_HELPERS_ADB_HPP
#define VPZ_APKSTUDIO_HELPERS_ADB_HPP

#include <QRegularExpression>
#include "cli.hpp"
#include "resources/constant.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class ADB : public CLI
{
    Q_OBJECT
public:
    explicit ADB(const QString &, QObject * = 0);
    QMap<QString, QString> properties(const QString &) const;
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_ADB_HPP
