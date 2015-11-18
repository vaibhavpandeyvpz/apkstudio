#include "include/buildrunnable.h"
#include "include/apktool.h"

APP_NAMESPACE_START

BuildRunnable::BuildRunnable(const QString &p, const QString &a, QObject *o)
    : Runnable(o), _apk(a), _project(p)
{
    _connections << connect(this, SIGNAL(buildFailure(QString)), o, SLOT(onBuildFailure(QString)), Qt::QueuedConnection);
    _connections << connect(this, SIGNAL(buildSuccess(QString)), o, SLOT(onBuildSuccess(QString)), Qt::QueuedConnection);
}

void BuildRunnable::run()
{
    emit runnableStarted();
    Process::Result r = ApkTool::get()->build(_project, _apk);
    if (r.code == 0)
    {
        emit buildSuccess(_apk);
    }
    else
    {
        emit buildFailure(_project);
    }
    emit runnableStopped();
}

APP_NAMESPACE_END
