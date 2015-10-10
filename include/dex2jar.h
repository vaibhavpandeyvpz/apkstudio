#ifndef DEX2JAR_H
#define DEX2JAR_H

#include "process.h"

APP_NAMESPACE_START

class Dex2Jar : public Process
{
private:
    static Dex2Jar *_self;
public:
    explicit Dex2Jar(QObject *parent = 0);
public:
    static Dex2Jar *get();
};

APP_NAMESPACE_END

#endif // DEX2JAR_H
