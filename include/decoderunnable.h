#ifndef DECODERUNNABLE_H
#define DECODERUNNABLE_H

#include "macros.h"
#include "runnable.h"

APP_NAMESPACE_START

class DecodeRunnable : public Runnable
{
    Q_OBJECT
private:
    QString _apk;
    QString _framework;
    QString _project;
    bool _resources;
    bool _sources;
public:
    explicit DecodeRunnable(const QString &apk, const QString &project, const QString &framework, const bool sources, const bool resources, QObject *parent = 0);
    void run();
Q_SIGNALS:
    void decodeFailure(const QString &apk);
    void decodeSuccess(const QString &dir);
};

APP_NAMESPACE_END

#endif // DECODERUNNABLE_H
