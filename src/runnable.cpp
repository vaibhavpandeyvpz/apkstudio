#include "include/runnable.h"

APP_NAMESPACE_START

Runnable::Runnable(QObject *p)
    : QObject(p)
{
    _connections << connect(this, SIGNAL(runnableStarted()), p, SLOT(onRunnableStarted()), Qt::QueuedConnection);
    _connections << connect(this, SIGNAL(runnableStopped()), p, SLOT(onRunnableStopped()), Qt::QueuedConnection);
    setAutoDelete(false);
}

Runnable::~Runnable()
{
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
