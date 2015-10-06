#include "adb.h"
#include "constants.h"

AS_NAMESPACE_START

Adb* Adb::_self = nullptr;

Adb::Adb(QObject *parent)
#ifdef Q_OS_WIN
    : Process("adb.exe", parent)
#else
    : Process("adb", parent)
#endif
{
}

Adb *Adb::get()
{
    if (!_self)
    {
        _self = new Adb();
    }
    return _self;
}

QString Adb::getVersion()
{
    Process::Result r = exec("version");
    QRegularExpression rgx(REGEX_ADB_VERSION);
    for (const QString &l : r.output)
    {
        QRegularExpressionMatch m;
        if ((m = rgx.match(l)).hasMatch())
        {
            QString v("%1.%2.%3");
            for (int i = 1; i <= 3; i++)
            {
                v = v.arg(m.captured(i));
            }
            return v;
        }
    }
    return QString();
}

Process::Result Adb::install(const QString &a)
{
    return exec(QStringList("install") << "-r" << a);
}

AS_NAMESPACE_END
