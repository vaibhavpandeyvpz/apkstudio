#ifndef INSTALLRUNNABLE_H
#define INSTALLRUNNABLE_H

#include "macros.h"
#include "runnable.h"

AS_NAMESPACE_START

class InstallRunnable : public Runnable
{
    Q_OBJECT
private:
    QString _apk;
public:
    explicit InstallRunnable(const QString &apk, QObject *parent = 0);
    void run();
signals:
    void installFailure(const QString &apk);
    void installSuccess(const QString &apk);
};

AS_NAMESPACE_END

#endif // INSTALLRUNNABLE_H
