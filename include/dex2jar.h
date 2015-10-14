#ifndef DEX2JAR_H
#define DEX2JAR_H

#include "java.h"

APP_NAMESPACE_START

class Dex2Jar : public Java
{
private:
    QStringList _cp;
    static Dex2Jar *_self;
public:
    explicit Dex2Jar(QObject *parent = 0);
public:
    Result exec(const QStringList &args);
    static Dex2Jar *get();
};

APP_NAMESPACE_END

#endif // DEX2JAR_H
