#ifndef SIGNRUNNABLE_H
#define SIGNRUNNABLE_H

#include "macros.h"
#include "runnable.h"

APP_NAMESPACE_START

class SignRunnable : public Runnable
{
    Q_OBJECT
private:
    QString _key;
    QString _keyPass;
    QString _keystore;
    QString _keystorePass;
    QString _src;
public:
    explicit SignRunnable(const QString &src, const QString &keyStore, const QString &keyStorePass, const QString &key, const QString &keyPass, QObject *parent = 0);
    void run();
Q_SIGNALS:
    void signFailure(const QString &apk);
    void signSuccess(const QString &apk);
};

APP_NAMESPACE_END

#endif // SIGNRUNNABLE_H
