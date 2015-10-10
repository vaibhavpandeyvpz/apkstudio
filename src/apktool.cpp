#include "apktool.h"
#include "constants.h"
#include "pathutils.h"
#include "textutils.h"

APP_NAMESPACE_START

ApkTool* ApkTool::_self = nullptr;

ApkTool::ApkTool(QObject *parent)
    : Java(parent)
{
    _jar = PathUtils::find("apktool.jar");
}

Process::Result ApkTool::build(const QString &s, const QString &d)
{
    return exec(QStringList("-f") << "b" << s << "-o" << d);
}

Process::Result ApkTool::decode(const QString &s, const QString &d, const QString &f)
{
    QStringList args("-f");
    args << "d" << s << "-o" << d;
    if (!f.isNull() && !f.isEmpty())
    {
        args << "-t" << f;
    }
    return exec(args);
}

Process::Result ApkTool::exec(const QStringList &a)
{
    return Java::exec(QStringList("-jar") << _jar << a);
}

ApkTool *ApkTool::get()
{
    if (!_self)
    {
        _self = new ApkTool();
    }
    return _self;
}

QString ApkTool::getVersion()
{
    Process::Result r = exec("-version");
    QRegularExpression rgx(REGEX_APKTOOL_VERSION);
    for (const QString &l : r.output)
    {
        QRegularExpressionMatch m = rgx.match(l);
        if (m.hasMatch())
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

APP_NAMESPACE_END
