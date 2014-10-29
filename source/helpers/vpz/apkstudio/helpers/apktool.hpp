#ifndef VPZ_APKSTUDIO_HELPERS_APKTOOL_HPP
#define VPZ_APKSTUDIO_HELPERS_APKTOOL_HPP

#include <QFileInfo>
#include "cli.hpp"
#include "settings.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class apktool : public CLI
{
    Q_OBJECT
public:
    explicit apktool(QObject *parent = 0);
    bool decompile(const QString &apk, const QString &folder, const QString &tag = QString()) { return decompile(QFileInfo(apk), QFileInfo(folder), tag); }
    bool decompile(const QFileInfo &, const QFileInfo &, const QString &tag = QString());
    inline bool install(const QString &path, const QString &tag) { return install(QFileInfo(path), tag); }
    bool install(const QFileInfo &, const QString &);
    bool recompile(const QString &folder, const QString &apk) { return recompile(QFileInfo(folder), QFileInfo(apk)); }
    bool recompile(const QFileInfo &, const QFileInfo &);
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_APKTOOL_HPP
