#ifndef JARSIGNER_H
#define JARSIGNER_H

#include "macros.h"
#include "process.h"

APP_NAMESPACE_START

class JarSigner : public Process
{
private:
    static JarSigner *_self;
private:
    explicit JarSigner(QObject *parent = 0);
public:
    static JarSigner *get();
    Result sign(const QString &src, const QString &dest, const QString &keystore, const QString &keystorePass, const QString &key, const QString &keyPass = QString());
};

APP_NAMESPACE_END

#endif // JARSIGNER_H
