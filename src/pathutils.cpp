#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>
#include "constants.h"
#include "pathutils.h"
#include "preferences.h"
#include "textutils.h"
#ifdef Q_OS_WIN
//#include "windows.h"
#endif

APP_NAMESPACE_START

QString PathUtils::combine(const QString &l, const QString &r)
{
    return TextUtils::rtrim(l, '/') + '/' + TextUtils::ltrim(r, '/');
}

QString PathUtils::find(const QString &exe)
{
    QString binary;
    if (QFile::exists(binary = PathUtils::combine(Preferences::get()->binariesPath(), exe)))
    {
        return binary;
    }
    QString relative;
    if (QFile::exists(relative = PathUtils::combine(QCoreApplication::applicationDirPath(), PathUtils::combine(FOLDER_BINARIES, exe))))
    {
        return relative;
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
#ifdef Q_OS_WIN
//    WCHAR b[MAX_PATH];
//    GetSystemDirectory(b, MAX_PATH);
//    QString sys = QString::fromWCharArray(b);
//    if (!sys.isEmpty() && (tmp = QDir(sys)).exists())
//    {
//        if (QFile::exists(bin = tmp.absoluteFilePath(exec)))
//        {
//            return bin;
//        }
//    }
#endif
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
    auto generator = [] (const QString &chars) -> QChar { return chars.at(rand() % chars.length()); };
    for (int i = 0; i < 8; i++)
    {
        prefix += generator("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }
    return combine(d.isEmpty() ? QDir::tempPath() : d, prefix + '-' + n);
}

APP_NAMESPACE_END
