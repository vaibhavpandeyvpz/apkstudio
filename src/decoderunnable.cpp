#include "decoderunnable.h"
#include "apktool.h"

APP_NAMESPACE_START

DecodeRunnable::DecodeRunnable(const QString &s, const QString &d, const QString &f, QObject *p)
    : Runnable(p), _dest(d), _framework(f), _src(s)
{
    _connections << connect(this, SIGNAL(decodeFailure(QString)), p, SLOT(onDecodeFailure(QString)), Qt::QueuedConnection);
    _connections << connect(this, SIGNAL(decodeSuccess(QString)), p, SLOT(onDecodeSuccess(QString)), Qt::QueuedConnection);
}

void DecodeRunnable::run()
{
    emit runnableStarted();
    Process::Result r = ApkTool::get()->decode(_src, _dest, _framework);
    if (r.code == 0)
    {
        emit decodeSuccess(_dest);
    }
    else
    {
        emit decodeFailure(_src);
    }
    emit runnableStopped();
}

APP_NAMESPACE_END
