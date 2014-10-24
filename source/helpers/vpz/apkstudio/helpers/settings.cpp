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
    set(SETTING_RECENT_FILES, QVariant(files));
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
    set(SETTING_RECENT_FILES, QVariant(files));
}

void Settings::addRecentProject(const QString &path)
{
    if (!QFile::exists(path))
        return;
    QStringList projects = recentProjects();
    if (projects.contains(path))
        return;
    projects.push_front(path);
    set(SETTING_RECENT_PROJECTS, QVariant(projects));
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
    set(SETTING_RECENT_PROJECTS, QVariant(projects));
}

int Settings::characterEncoding()
{
    int encoding = qvariant_cast<int>(get(SETTING_CHARACTER_ENCODING, QVariant(-1)));
    return (encoding < 0) ? QTextCodec::codecForName("UTF-8")->mibEnum() : encoding;
}

void Settings::characterEncoding(const int encoding)
{
    set(SETTING_CHARACTER_ENCODING, QVariant(encoding));
}

int Settings::cursorWidth()
{
    return qvariant_cast<int>(get(SETTING_CURSOR_WIDTH, QVariant(2)));
}

void Settings::cursorWidth(const int pixels)
{
    set(SETTING_CURSOR_WIDTH, QVariant(pixels));
}

QString Settings::fontFamily()
{
    return qvariant_cast<QString>(get(SETTING_FONT_FAMILY, QVariant("Source Code Pro")));
}

void Settings::fontFamily(const QString &family)
{
    set(SETTING_FONT_FAMILY, QVariant(family));
}

int Settings::fontSize()
{
    return qvariant_cast<int>(get(SETTING_FONT_SIZE, QVariant(10)));
}

void Settings::fontSize(const int size)
{
    set(SETTING_FONT_SIZE, QVariant(size));
}

QVariant Settings::get(const QString &key, const QVariant &fallback = QVariant())
{
    QSettings settings;
    return settings.value(key, fallback);
}

QString Settings::imageBackground()
{
    return qvariant_cast<QString>(get(SETTING_IMAGE_BACKGROUND, QVariant("#999999")));
}

void Settings::imageBackground(const QString &color)
{
    set(SETTING_IMAGE_BACKGROUND, QVariant(color));
}

QString Settings::language()
{
    return qvariant_cast<QString>(get(SETTING_LANGUAGE, QVariant("en")));
}

void Settings::language(const QString &name)
{
    set(SETTING_LANGUAGE, QVariant(name));
}

bool Settings::maximized()
{
    return qvariant_cast<bool>(get(SETTING_MAXIMIZED, QVariant(false)));
}

void Settings::maximized(const bool maximized)
{
    set(SETTING_MAXIMIZED, QVariant(maximized));
}

QString Settings::previousDirectory()
{
    QString directory = qvariant_cast<QString>(get(SETTING_PREVIOUS_DIRECTORY, QVariant("")));
    if (directory.isEmpty() || !QDir(directory).exists())
        directory = QDir::homePath();
    return directory;
}

void Settings::previousDirectory(const QString &directory)
{
    set(SETTING_PREVIOUS_DIRECTORY, QVariant(directory));
}

QStringList Settings::recentFiles()
{
    return qvariant_cast<QStringList>(get(SETTING_RECENT_FILES, QStringList()));
}

QStringList Settings::recentProjects()
{
    return qvariant_cast<QStringList>(get(SETTING_RECENT_PROJECTS, QStringList()));
}

void Settings::removeRecentFile(const QString &path)
{
    QStringList files = recentFiles();
    if (!files.contains(path))
        return;
    files.removeAll(path);
    set(SETTING_RECENT_FILES, QVariant(files));
}

void Settings::removeRecentProject(const QString &path)
{
    QStringList projects = recentProjects();
    if (!projects.contains(path))
        return;
    projects.removeAll(path);
    set(SETTING_RECENT_PROJECTS, QVariant(projects));
}

void Settings::set(const QString &key, const QVariant &value)
{
    QSettings settings;
    settings.setValue(key, value);
    settings.sync();
}

bool Settings::showWhitespace()
{
    return qvariant_cast<bool>(get(SETTING_SHOW_WHITESPACE, QVariant(false)));
}

void Settings::showWhitespace(const bool show)
{
    set(SETTING_SHOW_WHITESPACE, QVariant(show));
}

bool Settings::spacesForTab()
{
    return qvariant_cast<bool>(get(SETTING_SPACES_FOR_TAB, QVariant(true)));
}

void Settings::spacesForTab(const bool enable)
{
    set(SETTING_SPACES_FOR_TAB, QVariant(enable));
}

int Settings::tabWidth()
{
    return qvariant_cast<int>(get(SETTING_TAB_WIDTH, QVariant(4)));
}

void Settings::tabWidth(const int count)
{
    set(SETTING_TAB_WIDTH, QVariant(count));
}

QString Settings::theme()
{
    return qvariant_cast<QString>(get(SETTING_THEME, QVariant("dark")));
}

void Settings::theme(const QString &name)
{
    set(SETTING_THEME, QVariant(name));
}

QSize Settings::windowSize()
{
    return qvariant_cast<QSize>(get(SETTING_WINDOW_SIZE, QVariant(QSize(800, 600))));
}

void Settings::windowSize(const QSize &size)
{
    set(SETTING_WINDOW_SIZE, QVariant(size));
}

bool Settings::wordWrap()
{
    return qvariant_cast<bool>(get(SETTING_WORD_WRAP, QVariant(false)));
}

void Settings::wordWrap(const bool enable)
{
    set(SETTING_WORD_WRAP, QVariant(enable));
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
