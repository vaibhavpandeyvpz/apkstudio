#include "runnable.h"

AS_NAMESPACE_START

Runnable::Runnable(QObject *p)
    : QObject(p)
{
    _connections << connect(this, SIGNAL(runnableStarted()), p, SLOT(onRunnableStarted()), Qt::QueuedConnection);
    _connections << connect(this, SIGNAL(runnableStopped()), p, SLOT(onRunnableStopped()), Qt::QueuedConnection);
    setAutoDelete(false);
}

Runnable::~Runnable()
{
    AS_CONNECTIONS_DISCONNECT
}

AS_NAMESPACE_END
