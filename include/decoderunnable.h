#ifndef DECODERUNNABLE_H
#define DECODERUNNABLE_H

#include "macros.h"
#include "runnable.h"

APP_NAMESPACE_START

class DecodeRunnable : public Runnable
{
    Q_OBJECT
private:
    QString _dest;
    QString _framework;
    QString _src;
public:
    explicit DecodeRunnable(const QString &src, const QString &dest, const QString &framework, QObject *parent = 0);
    void run();
Q_SIGNALS:
    void decodeFailure(const QString &apk);
    void decodeSuccess(const QString &dir);
};

APP_NAMESPACE_END

#endif // DECODERUNNABLE_H
