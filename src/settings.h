#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDir>
#include <QFile>
#include <QSize>
#include <QTextCodec>

#include "constant.h"
#include "settingsabstract.h"

class Settings : public SettingsAbstract
{
public:
    static void addRecentFile(const QString &);
    static void addRecentFiles(const QStringList &);
    static void addRecentProject(const QString &);
    static void addRecentProjects(const QStringList &);
    static int characterEncoding();
    static void characterEncoding(const int);
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
    static QSize windowSize();
    static void windowSize(const QSize &);
};

#endif // SETTINGS_H
