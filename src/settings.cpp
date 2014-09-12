#include "settings.h"

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

QString Settings::imageBackground()
{
    return qvariant_cast<QString>(get(SETTING_IMAGE_BACKGROUND, QVariant("#ffffff")));
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

void Settings::maximized(bool maximized)
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

QSize Settings::windowSize()
{
    return qvariant_cast<QSize>(get(SETTING_WINDOW_SIZE, QVariant(QSize(800, 600))));
}

void Settings::windowSize(const QSize &size)
{
    set(SETTING_WINDOW_SIZE, QVariant(size));
}
