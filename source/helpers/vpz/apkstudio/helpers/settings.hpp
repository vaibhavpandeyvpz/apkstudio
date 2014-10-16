#ifndef VPZ_APKSTUDIO_HELPERS_SETTINGS_HPP
#define VPZ_APKSTUDIO_HELPERS_SETTINGS_HPP

#include <QDir>
#include <QFile>
#include <QSettings>
#include <QSize>
#include <QTextCodec>

#include "resources/constant.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class Settings
{
public:
    static void addRecentFile(const QString &);
    static void addRecentFiles(const QStringList &);
    static void addRecentProject(const QString &);
    static void addRecentProjects(const QStringList &);
    static int characterEncoding();
    static void characterEncoding(const int);
    static QVariant get(const QString &, const QVariant &);
    static QString imageBackground();
    static void imageBackground(const QString &);
    static QString language();
    static void language(const QString &);
    static bool maximized();
    static void maximized(bool);
    static QString previousDirectory();
    static void previousDirectory(const QString &);
    static QStringList recentFiles();
    static QStringList recentProjects();
    static void removeRecentFile(const QString &);
    static void removeRecentProject(const QString &);
    static void set(const QString &, const QVariant &);
    static QSize windowSize();
    static void windowSize(const QSize &);
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_SETTINGS_HPP
