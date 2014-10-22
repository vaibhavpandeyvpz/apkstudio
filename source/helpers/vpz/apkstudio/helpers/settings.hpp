#ifndef VPZ_APKSTUDIO_HELPERS_SETTINGS_HPP
#define VPZ_APKSTUDIO_HELPERS_SETTINGS_HPP

#include <QDir>
#include <QFile>
#include <QHash>
#include <QSettings>
#include <QSize>
#include <QTextCodec>
#include <QVariant>
#include <QXmlStreamReader>
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
    static int cursorWidth();
    static void cursorWidth(const int);
    static QString fontFamily();
    static void fontFamily(const QString &);
    static int fontSize();
    static void fontSize(const int);
    static QVariant get(const QString &, const QVariant &);
    static QString imageBackground();
    static void imageBackground(const QString &);
    static QString language();
    static void language(const QString &);
    inline static QStringList brackets() { return QString("(),{},[]").split(','); }
    static bool maximized();
    static void maximized(const bool);
    static QString previousDirectory();
    static void previousDirectory(const QString &);
    static QStringList recentFiles();
    static QStringList recentProjects();
    static void removeRecentFile(const QString &);
    static void removeRecentProject(const QString &);
    static void set(const QString &, const QVariant &);
    static bool showWhitespace();
    static void showWhitespace(const bool);
    static bool spacesForTab();
    static void spacesForTab(const bool);
    static int tabWidth();
    static void tabWidth(const int);
    static QString theme();
    static void theme(const QString &);
    static QSize windowSize();
    static void windowSize(const QSize &);
    static bool wordWrap();
    static void wordWrap(const bool);
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_SETTINGS_HPP
