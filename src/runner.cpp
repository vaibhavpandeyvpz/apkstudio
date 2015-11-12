#include "include/constants.h"
#include "include/runner.h"

APP_NAMESPACE_START

Runner* Runner::_self = NULL;

Runner::Runner(QObject *p)
    : QObject(p), _pool(new QThreadPool(this))
{
    _pool->setMaxThreadCount(THREADS_MAX);
}

void Runner::add(Runnable *r)
{
    _connections << connect(r, &Runnable::runnableStopped, r, &Runnable::deleteLater, Qt::QueuedConnection);
    _pool->start(r);
}

Runner *Runner::get()
{
    if (!_self)
    {
        _self = new Runner();
    }
    return _self;
}

Runner::~Runner()
{
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
