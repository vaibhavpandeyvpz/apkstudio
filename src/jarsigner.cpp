#include "jarsigner.h"
#include "constants.h"

APP_NAMESPACE_START

JarSigner* JarSigner::_self = nullptr;

JarSigner::JarSigner(QObject *parent)
#ifdef Q_OS_WIN
    : Process("jarsigner.exe", parent)
#else
    : Process("jarsigner", parent)
#endif
{
}

Process::Result JarSigner::sign(const QString &s, const QString &d, const QString &ks, const QString &ksp, const QString &k, const QString &kp)
{
    QStringList args("-verbose");
    args << "-sigalg" << "SHA1withRSA" << "-digestalg" << "SHA1";
    args << "-keystore" << ks << "-storepass" << ksp;
    if (!kp.isEmpty())
    {
        args << "-keypass" << kp;
    }
    return exec(args << "-signedjar" << d << s << k);
}

JarSigner *JarSigner::get()
{
    if (!_self)
    {
        _self = new JarSigner();
    }
    return _self;
}

APP_NAMESPACE_END
