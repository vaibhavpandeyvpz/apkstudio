#include "decoderunnable.h"
#include "apktool.h"

AS_NAMESPACE_START

DecodeRunnable::DecodeRunnable(const QString &s, const QString &d, QObject *p)
    : Runnable(p), _src(s), _dest(d)
{
    _connections << connect(this, SIGNAL(decodeFailure(QString)), p, SLOT(onDecodeFailure(QString)), Qt::QueuedConnection);
    _connections << connect(this, SIGNAL(decodeSuccess(QString)), p, SLOT(onDecodeSuccess(QString)), Qt::QueuedConnection);
}

void DecodeRunnable::run()
{
    emit runnableStarted();
    Process::Result r = ApkTool::get()->decode(_src, _dest);
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

AS_NAMESPACE_END
