#ifndef DECODERUNNABLE_H
#define DECODERUNNABLE_H

#include "macros.h"
#include "runnable.h"

AS_NAMESPACE_START

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
signals:
    void decodeFailure(const QString &apk);
    void decodeSuccess(const QString &dir);
};

AS_NAMESPACE_END

#endif // DECODERUNNABLE_H
