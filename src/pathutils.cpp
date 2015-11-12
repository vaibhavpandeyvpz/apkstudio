#include <QDir>
#include <QStandardPaths>
#include "include/constants.h"
#include "include/pathutils.h"
#include "include/preferences.h"
#include "include/textutils.h"

APP_NAMESPACE_START

QString PathUtils::combine(const QString &l, const QString &r)
{
    return TextUtils::rtrim(l, '/') + '/' + TextUtils::ltrim(r, '/');
}

QString PathUtils::find(const QString &exe)
{
    QString vendor;
    if (QFile::exists(vendor = PathUtils::combine(Preferences::get()->vendorPath(), exe)))
    {
        return vendor;
    }
    if (QFile::exists(exe))
    {
        return exe;
    }
    QString bin;
    if (QFile::exists(bin = QStandardPaths::findExecutable(exe)))
    {
        return bin;
    }
    QDir tmp;
    QString jdk(qgetenv("JAVA_HOME"));
    if (!jdk.isEmpty() && (tmp = QDir(PathUtils::combine(jdk, "bin"))).exists())
    {
        if (QFile::exists(bin = tmp.absoluteFilePath(exe)))
        {
            return bin;
        }
    }
    QString sdk(qgetenv("ANDROID_SDK_HOME"));
    if (!sdk.isEmpty() && (tmp = QDir(PathUtils::combine(sdk, "platform-tools"))).exists())
    {
        if (QFile::exists(bin = tmp.absoluteFilePath(exe)))
        {
            return bin;
        }
    }
    return exe;
}

QString PathUtils::temp(const QString &n, const QString &d)
{
    QString prefix;
    const QString &chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 8; i++)
    {
        prefix += chars.at(rand() % chars.length());
    }
    return combine(d.isEmpty() ? QDir::tempPath() : d, prefix + '-' + n);
}

APP_NAMESPACE_END
