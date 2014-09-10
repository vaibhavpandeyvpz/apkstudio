#ifndef SETTINGSABSTRACT_H
#define SETTINGSABSTRACT_H

#include <QSettings>

class SettingsAbstract
{
public:
    static QVariant get(const QString &, const QVariant &);
    static void set(const QString &, const QVariant &);
    static void sync();
};

#endif // SETTINGSABSTRACT_H
