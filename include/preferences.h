#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QPointer>
#include <QSettings>
#include "macros.h"

APP_NAMESPACE_START

class Preferences
{
private:
    QString _appPath;
    static Preferences *_self;
    QSettings *_settings;
private:
    Preferences(const QString &path);
public:
    static Preferences *get();
    QVariant get(const QString &key, const QVariant &fallback = QVariant());
    void save();
    Preferences *set(const QString &key, const QVariant &value);
    // Getters
    QString appPath();
    QString vendorPath();
    QByteArray docksState();
    int javaHeap();
    QString previousApk();
    QString previousDir();
    QStringList sessionFiles();
    QString sessionProject();
    bool showWhitespaces();
    QString signKey();
    QString signKeyPass();
    QString signKeystore();
    QString signKeystorePass();
    int tabStopWidth();
    int textEncoding();
    bool useSpacesForTabs();
    bool wasWindowMaximized();
    QSize windowSize();
    // Setters
    Preferences *setVendorPath(const QString &path);
    Preferences *setDocksState(const QByteArray &state);
    Preferences *setJavaHeap(const int mb);
    Preferences *setPreviousDir(const QString &dir);
    Preferences *setSessionFiles(const QStringList &files);
    Preferences *setSessionProject(const QString &project);
    Preferences *setShowWhitespaces(const bool show);
    Preferences *setSignKey(const QString &name);
    Preferences *setSignKeyPass(const QString &pass);
    Preferences *setSignKeystore(const QString &keystore);
    Preferences *setSignKeystorePass(const QString &pass);
    Preferences *setTabStopWidth(const int width);
    Preferences *setTextEncoding(const int codec);
    Preferences *setUseSpacesForTabs(const bool use);
    Preferences *setWindowMaximized(const bool maximized);
    Preferences *setWindowSize(const QSize &size);
};

APP_NAMESPACE_END

#endif // PREFERENCES_H
