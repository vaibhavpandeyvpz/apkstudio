#ifndef ADB_H
#define ADB_H

#include "macros.h"
#include "process.h"

AS_NAMESPACE_START

class Adb : public Process
{
private:
    static Adb *_self;
private:
    explicit Adb(QObject *parent = 0);
public:
    static Adb *get();
    QString getVersion();
    Result install(const QString &apk);
};

AS_NAMESPACE_END

#endif // ADB_H
