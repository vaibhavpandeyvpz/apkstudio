#include "include/zipalign.h"
#include "include/constants.h"

APP_NAMESPACE_START

ZipAlign* ZipAlign::_self = nullptr;

ZipAlign::ZipAlign(QObject *parent)
#ifdef Q_OS_WIN
    : Process("zipalign.exe", parent)
#else
    : Process("zipalign", parent)
#endif
{
}

Process::Result ZipAlign::align(const QString &src, const QString &dest)
{
    return exec(QStringList("-f") << "-v" << "4" << src << dest);
}

ZipAlign *ZipAlign::get()
{
    if (!_self)
    {
        _self = new ZipAlign();
    }
    return _self;
}

APP_NAMESPACE_END
