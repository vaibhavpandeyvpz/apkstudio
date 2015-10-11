#ifndef RUNNER_H
#define RUNNER_H

#include <QThreadPool>
#include "macros.h"
#include "runnable.h"

APP_NAMESPACE_START

class Runner : public QObject
{
    Q_OBJECT
protected:
    APP_CONNECTIONS_LIST
    QThreadPool *_pool;
    static Runner *_self;
public:
    explicit Runner(QObject *parent = 0);
    ~Runner();
public:
    void add(Runnable *runnable);
    static Runner *get();
};

APP_NAMESPACE_END

#endif // RUNNER_H
