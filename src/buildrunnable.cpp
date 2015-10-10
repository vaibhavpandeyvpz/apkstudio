#include "buildrunnable.h"
#include "apktool.h"

APP_NAMESPACE_START

BuildRunnable::BuildRunnable(const QString &s, const QString &d, QObject *p)
    : Runnable(p), _dest(d), _src(s)
{
    _connections << connect(this, SIGNAL(buildFailure(QString)), p, SLOT(onBuildFailure(QString)), Qt::QueuedConnection);
    _connections << connect(this, SIGNAL(buildSuccess(QString)), p, SLOT(onBuildSuccess(QString)), Qt::QueuedConnection);
}

void BuildRunnable::run()
{
    emit runnableStarted();
    Process::Result r = ApkTool::get()->build(_src, _dest);
    if (r.code == 0)
    {
        emit buildSuccess(_dest);
    }
    else
    {
        emit buildFailure(_src);
    }
    emit runnableStopped();
}

APP_NAMESPACE_END
