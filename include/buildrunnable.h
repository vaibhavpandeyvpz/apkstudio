#ifndef BUILDRUNNABLE_H
#define BUILDRUNNABLE_H

#include "macros.h"
#include "runnable.h"

APP_NAMESPACE_START

class BuildRunnable : public Runnable
{
    Q_OBJECT
private:
    QString _dest;
    QString _src;
public:
    explicit BuildRunnable(const QString &src, const QString &dest, QObject *parent);
    void run();
Q_SIGNALS:
    void buildFailure(const QString &dir);
    void buildSuccess(const QString &apk);
};

APP_NAMESPACE_END

#endif // BUILDTASK_H
