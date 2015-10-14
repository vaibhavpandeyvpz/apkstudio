#include <QDir>
#include "include/dex2jar.h"
#include "include/pathutils.h"
#include "include/preferences.h"

APP_NAMESPACE_START

Dex2Jar* Dex2Jar::_self = nullptr;

Dex2Jar::Dex2Jar(QObject *p)
    : Java(p)
{
    QDir d2j(PathUtils::combine(Preferences::get()->vendorPath(), "dex2jar"));
    if (d2j.exists())
    {
        QFileInfoList files = d2j.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst);
        for (QFileInfo fi : files)
        {
           if (fi.isFile() && QString::compare("jar", fi.suffix(), Qt::CaseInsensitive))
           {
               _cp.append(fi.absoluteFilePath());
           }
        }
    }
}

Process::Result Dex2Jar::exec(const QStringList &a)
{
    return Java::exec(QStringList("-cp") << _cp.join(';') << "com.googlecode.dex2jar.tools.Dex2jarCmd" << a);
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
