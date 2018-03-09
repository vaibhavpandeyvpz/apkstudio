#include "include/uberapksigner.h"
#include "include/constants.h"
#include "include/pathutils.h"
#include "include/textutils.h"

APP_NAMESPACE_START

UberApkSigner* UberApkSigner::_self = NULL;

UberApkSigner::UberApkSigner(QObject *parent)
    : Java(parent)
{
    _jar = PathUtils::find("uber-apk-signer.jar");
}

Process::Result UberApkSigner::sign(const QString &s, const QString &ks, const QString &ksp, const QString &k, const QString &kp)
{
    QStringList args("--debug");
    args << "-ks" << ks << "--ksPass" << ksp;
    if (!kp.isEmpty())
    {
        args << "--ksKeyPass" << kp;
    }
    return exec(args << "-a" << s << "--ksAlias" << k << "--overwrite" << "--allowResign");
}

Process::Result UberApkSigner::signDebug(const QString &s)
{
    QStringList args("--debug");
    return exec(args << "-a" << s << "--overwrite" << "--allowResign");
}

UberApkSigner *UberApkSigner::get()
{
    if (!_self)
    {
        _self = new UberApkSigner();
    }
    return _self;
}

Process::Result UberApkSigner::exec(const QStringList &a)
{
    return Java::exec(QStringList("-jar") << _jar << a);
}


QString UberApkSigner::getVersion()
{
    Process::Result r = exec("-version");
    QRegularExpression rgx(REGEX_UBERAPKTOOL_VERSION);
    foreach (const QString &l, r.output)
    {
        QRegularExpressionMatch m = rgx.match(l);
        if (m.hasMatch())
        {
            QString v("%1.%2.%3");
            for (int i = 1; i <= 3; i++)
            { v = v.arg(m.captured(i)); }
            return v;
        }
    }
    return QString();
}

APP_NAMESPACE_END

