#include "include/apktool.h"
#include "include/decoderunnable.h"

APP_NAMESPACE_START

DecodeRunnable::DecodeRunnable(const QString &a, const QString &p, const QString &f, const bool s, const bool r, QObject *o)
    : Runnable(o), _apk(a), _framework(f), _project(p), _resources(r), _sources(s)
{
    _connections << connect(this, SIGNAL(decodeFailure(QString)), o, SLOT(onDecodeFailure(QString)), Qt::QueuedConnection);
    _connections << connect(this, SIGNAL(decodeSuccess(QString)), o, SLOT(onDecodeSuccess(QString)), Qt::QueuedConnection);
}

void DecodeRunnable::run()
{
    emit runnableStarted();
    Process::Result r = ApkTool::get()->decode(_apk, _project, _framework, _sources, _resources);
    if (r.code == 0)
    {
        emit decodeSuccess(_project);
    }
    else
    {
        emit decodeFailure(_apk);
    }
    emit runnableStopped();
}

APP_NAMESPACE_END
