#ifndef JAVA_H
#define JAVA_H

#include "macros.h"
#include "process.h"

APP_NAMESPACE_START

class Java : public Process
{
private:
    static Java *_self;
protected:
    explicit Java(QObject *parent = 0);
public:
    inline Process::Result exec(const QString &arg) { return exec(QStringList(arg)); }
    virtual Process::Result exec(const QStringList &args);
    static Java *get();
    virtual QString getVersion();
};

APP_NAMESPACE_END

#endif // JAVA_H
