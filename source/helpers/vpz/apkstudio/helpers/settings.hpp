#ifndef VPZ_APKSTUDIO_HELPERS_SETTINGS_HPP
#define VPZ_APKSTUDIO_HELPERS_SETTINGS_HPP

#include <QDir>
#include <QFile>
#include <QHash>
#include <QProcessEnvironment>
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
    static QString binary(const QString &);
    static QString binaryPath();
    static void binaryPath(const QString &);
    static QStringList brackets(const QString &);
    static int characterEncoding();
    static void characterEncoding(const int);
    static int cursorWidth();
    static void cursorWidth(const int);
    static QStringList directoryIcons();
    static QByteArray dockState();
    static void dockState(const QByteArray &);
    static QStringList fileIcons();
    static QString fontFamily();
    static void fontFamily(const QString &);
    static int fontSize();
    static void fontSize(const int);
    static QString frameworkPath();
    static void frameworkPath(const QString &);
    static QVariant get(const QString &, const QVariant &);
    static int heapSize();
    static void heapSize(const int);
    static QString imageBackground();
    static void imageBackground(const QString &);
    static QString javaHome();
    static void javaHome(const QString &);
    static QString language();
    static void language(const QString &);
    static bool maximized();
    static void maximized(const bool);
    static QString previousDirectory();
    static void previousDirectory(const QString &);
    static QStringList recentFiles();
    static bool rootShell();
    static void rootShell(const bool);
    static void set(const QString &, const QVariant &);
    static bool showWhitespace();
    static void showWhitespace(const bool);
    static QString signingCertificate();
    static void signingCertificate(const QString &);
    static QString signingKey();
    static void signingKey(const QString &);
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
