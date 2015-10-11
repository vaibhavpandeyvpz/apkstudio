#include "include/dex2jar.h"
#include "include/pathutils.h"

APP_NAMESPACE_START

Dex2Jar* Dex2Jar::_self = nullptr;

Dex2Jar::Dex2Jar(QObject *p)
#ifdef Q_OS_WIN
    : Process("d2j-dex2jar.bat", p)
#else
    : Process("d2j-dex2jar.sh", p)
#endif
{
}

Dex2Jar *Dex2Jar::get()
{
    if (!_self)
    {
        _self = new Dex2Jar();
    }
    return _self;
}

APP_NAMESPACE_END
