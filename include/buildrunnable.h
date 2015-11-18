#ifndef BUILDRUNNABLE_H
#define BUILDRUNNABLE_H

#include "macros.h"
#include "runnable.h"

APP_NAMESPACE_START

class BuildRunnable : public Runnable
{
    Q_OBJECT
private:
    QString _apk;
    QString _project;
public:
    explicit BuildRunnable(const QString &project, const QString &apk, QObject *parent);
    void run();
Q_SIGNALS:
    void buildFailure(const QString &project);
    void buildSuccess(const QString &apk);
};

APP_NAMESPACE_END

#endif // BUILDTASK_H
