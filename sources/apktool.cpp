#include "apktool.h"
#include "constants.h"
#include "pathutils.h"
#include "textutils.h"

AS_NAMESPACE_START

ApkTool* ApkTool::_self = nullptr;

ApkTool::ApkTool(QObject *parent)
#ifdef Q_OS_WIN
    : Java(parent)
#else
    : Java(parent)
#endif
{
    _jar = PathUtils::find("apktool.jar");
}

Process::Result ApkTool::build(const QString &s, const QString &d)
{
    return exec(QStringList("-f") << "b" << s << "-o" << d);
}

Process::Result ApkTool::decode(const QString &s, const QString &d)
{
    return exec(QStringList("-f") << "d" << s << "-o" << d);
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

AS_NAMESPACE_END
