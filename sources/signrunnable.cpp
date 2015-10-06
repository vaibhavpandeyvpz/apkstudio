#include <QFile>
#include "jarsigner.h"
#include "pathutils.h"
#include "signrunnable.h"
#include "zipalign.h"

AS_NAMESPACE_START

SignRunnable::SignRunnable(const QString &s, const QString &ks, const QString &ksp, const QString &k, const QString &kp, QObject *p)
    : Runnable(p), _key(k), _keyPass(kp), _keystore(ks),  _keystorePass(ksp), _src(s)
{
    _connections << connect(this, SIGNAL(signFailure(QString)), p, SLOT(onSignFailure(QString)), Qt::QueuedConnection);
    _connections << connect(this, SIGNAL(signSuccess(QString)), p, SLOT(onSignSuccess(QString)), Qt::QueuedConnection);
}

void SignRunnable::run()
{
    emit runnableStarted();
    QString tmp = PathUtils::temp("signed.apk");
    Process::Result r = JarSigner::get()->sign(_src, tmp, _keystore, _keystorePass, _key, _keyPass);
    if (r.code == 0)
    {
        r = ZipAlign::get()->align(tmp, _src);
        if (r.code == 0)
        {
            emit signSuccess(_src);
        }
        else
        {
            emit signFailure(_src);
        }
        QFile::remove(tmp);
    }
    else
    {
        emit signFailure(_src);
    }
    emit runnableStopped();
}

AS_NAMESPACE_END
