#include "settingsabstract.h"

QVariant SettingsAbstract::get(const QString &key, const QVariant &fallback = QVariant())
{
    QSettings settings;
    return settings.value(key, fallback);
}

void SettingsAbstract::set(const QString &key, const QVariant &value)
{
    QSettings settings;
    settings.setValue(key, value);
    settings.sync();
}
