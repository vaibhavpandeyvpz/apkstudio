#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QSettings>
#include "macros.h"

class Preferences
{
private:
    static Preferences *_self;
    QSettings *_settings;
private:
    Preferences(QSettings *settings);
public:
    static Preferences *get();
    QVariant get(const QString &key, const QVariant &fallback = QVariant());
    void save();
    Preferences *set(const QString &key, const QVariant &value);
    // Getters
    QString binariesPath();
    QByteArray docksState();
    int javaHeap();
    QString previousApk();
    QString previousDir();
    QString previousProject();
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
    Preferences *setBinariesPath(const QString &path);
    Preferences *setDocksState(const QByteArray &state);
    Preferences *setJavaHeap(const int mb);
    Preferences *setPreviousDir(const QString &dir);
    Preferences *setPreviousProject(const QString &project);
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

#endif // PREFERENCES_H
