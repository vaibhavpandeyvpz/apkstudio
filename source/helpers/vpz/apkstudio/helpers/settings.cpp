#include "settings.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

void Settings::addRecentFile(const QString &path)
{
    if (!QFile::exists(path))
        return;
    QStringList files = recentFiles();
    if (files.contains(path))
        return;
    files.push_front(path);
    set(SETTING_RECENT_FILES, files);
}

void Settings::addRecentFiles(const QStringList &paths)
{
    QStringList files = recentFiles();
    foreach (const QString &path, paths) {
        if (!QFile::exists(path))
            continue;
        if (files.contains(path))
            return;
        files.push_front(path);
    }
    set(SETTING_RECENT_FILES, files);
}

void Settings::addRecentProject(const QString &path)
{
    if (!QFile::exists(path))
        return;
    QStringList projects = recentProjects();
    if (projects.contains(path))
        return;
    projects.push_front(path);
    set(SETTING_RECENT_PROJECTS, projects);
}

void Settings::addRecentProjects(const QStringList &paths)
{
    QStringList projects = recentProjects();
    foreach (const QString &path, paths) {
        if (!QFile::exists(path))
            continue;
        if (projects.contains(path))
            return;
        projects.push_front(path);
    }
    set(SETTING_RECENT_PROJECTS, projects);
}

QString Settings::binary(const QString &executable)
{
    return QString(binaryPath()).append('/').append(executable);
}

QString Settings::binaryPath()
{
    QString path = get(SETTING_BINARY_PATH, "").value<QString>();
    if (path.isEmpty())
        path = QString(QDir::homePath()).append("/apkstudio/bin");
    return path;
}

void Settings::binaryPath(const QString &path)
{
    set(SETTING_BINARY_PATH, path);
}

QStringList Settings::brackets(const QString &mode)
{
    QString brackets;
    if (QString::compare(mode, "java") == 0)
        brackets.append("(),{}");
    else if (QString::compare(mode, "xml") == 0)
        brackets.append("<>");
    else if (QString::compare(mode, "smali") == 0)
        brackets.append("(),{}");
    return brackets.split(',');
}

int Settings::characterEncoding()
{
    int encoding = get(SETTING_CHARACTER_ENCODING, -1).value<int>();
    return (encoding < 0) ? QTextCodec::codecForName("UTF-8")->mibEnum() : encoding;
}

void Settings::characterEncoding(const int encoding)
{
    set(SETTING_CHARACTER_ENCODING, encoding);
}

int Settings::cursorWidth()
{
    return get(SETTING_CURSOR_WIDTH, 2).value<int>();
}

void Settings::cursorWidth(const int pixels)
{
    set(SETTING_CURSOR_WIDTH, pixels);
}

QByteArray Settings::dockState()
{
    return get(SETTING_DOCK_STATE, QByteArray()).value<QByteArray>();
}

void Settings::dockState(const QByteArray &state)
{
    set(SETTING_DOCK_STATE, state);
}

QString Settings::fontFamily()
{
    return get(SETTING_FONT_FAMILY, QVariant("Source Code Pro")).value<QString>();
}

void Settings::fontFamily(const QString &family)
{
    set(SETTING_FONT_FAMILY, family);
}

int Settings::fontSize()
{
    return get(SETTING_FONT_SIZE, 10).value<int>();
}

void Settings::fontSize(const int points)
{
    set(SETTING_FONT_SIZE, points);
}

QString Settings::frameworkPath()
{
    QString path = get(SETTING_FRAMEWORK_PATH, "").value<QString>();
    if (path.isEmpty())
        path = QDir::homePath().append("/apktool/framework");;
    return path;
}

void Settings::frameworkPath(const QString &path)
{
    set(SETTING_FRAMEWORK_PATH, path);
}

QVariant Settings::get(const QString &key, const QVariant &fallback = QVariant())
{
    QSettings settings;
    return settings.value(key, fallback);
}

int Settings::heapSize()
{
    return get(SETTING_HEAP_SIZE, 512).value<int>();
}

void Settings::heapSize(int mb)
{
    set(SETTING_HEAP_SIZE, mb);
}

QString Settings::imageBackground()
{
    return get(SETTING_IMAGE_BACKGROUND, "#999999").value<QString>();
}

void Settings::imageBackground(const QString &color)
{
    set(SETTING_IMAGE_BACKGROUND, color);
}

QString Settings::javaHome()
{
    QString java = get(SETTING_JAVA_HOME, "").value<QString>();
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    if (environment.contains("JAVA_HOME"))
        java = environment.value("JAVA_HOME");
    return java;
}

void Settings::javaHome(const QString &java)
{
    set(SETTING_JAVA_HOME, java);
}

QString Settings::language()
{
    return get(SETTING_LANGUAGE, "en").value<QString>();
}

void Settings::language(const QString &name)
{
    set(SETTING_LANGUAGE, name);
}

bool Settings::maximized()
{
    return get(SETTING_MAXIMIZED, false).value<bool>();
}

void Settings::maximized(const bool maximized)
{
    set(SETTING_MAXIMIZED, maximized);
}

QString Settings::previousDirectory()
{
    QString directory = get(SETTING_PREVIOUS_DIRECTORY, "").value<QString>();
    if (directory.isEmpty() || !QDir(directory).exists())
        directory = QDir::homePath();
    return directory;
}

void Settings::previousDirectory(const QString &directory)
{
    set(SETTING_PREVIOUS_DIRECTORY, directory);
}

QStringList Settings::recentFiles()
{
    return get(SETTING_RECENT_FILES, QStringList()).value<QStringList>();
}

QStringList Settings::recentProjects()
{
    return get(SETTING_RECENT_PROJECTS, QStringList()).value<QStringList>();
}

void Settings::removeRecentFile(const QString &path)
{
    QStringList files = recentFiles();
    if (!files.contains(path))
        return;
    files.removeAll(path);
    set(SETTING_RECENT_FILES, files);
}

void Settings::removeRecentProject(const QString &path)
{
    QStringList projects = recentProjects();
    if (!projects.contains(path))
        return;
    projects.removeAll(path);
    set(SETTING_RECENT_PROJECTS, projects);
}

bool Settings::rootShell()
{
    return get(SETTING_ROOT_SHELL, false).value<bool>();
}

void Settings::rootShell(const bool show)
{
    set(SETTING_ROOT_SHELL, show);
}

void Settings::set(const QString &key, const QVariant &value)
{
    QSettings settings;
    settings.setValue(key, value);
    settings.sync();
}

bool Settings::showWhitespace()
{
    return get(SETTING_SHOW_WHITESPACE, false).value<bool>();
}

void Settings::showWhitespace(const bool show)
{
    set(SETTING_SHOW_WHITESPACE, QVariant(show));
}

QString Settings::signingCertificate()
{
    QString certificate = get(SETTING_SIGNING_CERTIFICATE, "").value<QString>();
    if (certificate.isEmpty())
        certificate = binary("testkey.x509.pem");
    return certificate;
}

void Settings::signingCertificate(const QString &path)
{
    set(SETTING_SIGNING_CERTIFICATE, path);
}

QString Settings::signingKey()
{
    QString key = get(SETTING_SIGNING_KEY, "").value<QString>();
    if (key.isEmpty())
        key = binary("testkey.pk8");
    return key;
}

void Settings::signingKey(const QString &path)
{
    set(SETTING_SIGNING_KEY, path);
}

bool Settings::spacesForTab()
{
    return get(SETTING_SPACES_FOR_TAB, true).value<bool>();
}

void Settings::spacesForTab(const bool enable)
{
    set(SETTING_SPACES_FOR_TAB, enable);
}

int Settings::tabWidth()
{
    return get(SETTING_TAB_WIDTH, QVariant(4)).value<int>();
}

void Settings::tabWidth(const int count)
{
    set(SETTING_TAB_WIDTH, count);
}

QString Settings::theme()
{
    return get(SETTING_THEME, "light").value<QString>();
}

void Settings::theme(const QString &name)
{
    set(SETTING_THEME, name);
}

QSize Settings::windowSize()
{
    return get(SETTING_WINDOW_SIZE, QSize(800, 600)).value<QSize>();
}

void Settings::windowSize(const QSize &size)
{
    set(SETTING_WINDOW_SIZE, size);
}

bool Settings::wordWrap()
{
    return get(SETTING_WORD_WRAP, QVariant(false)).value<bool>();
}

void Settings::wordWrap(const bool enable)
{
    set(SETTING_WORD_WRAP, enable);
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
