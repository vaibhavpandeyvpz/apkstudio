#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <QRunnable>
#include <QObject>
#include "macros.h"

APP_NAMESPACE_START

class Runnable : public QObject, public QRunnable
{
    Q_OBJECT
protected:
    APP_CONNECTIONS_LIST
public:
    explicit Runnable(QObject *parent = 0);
    ~Runnable();
public:
    virtual void run() = 0;
signals:
    void runnableStarted();
    void runnableStopped();
};

APP_NAMESPACE_END

#endif // RUNNABLE_H
