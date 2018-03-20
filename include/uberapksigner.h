#ifndef UBERAPKSIGNER_H
#define UBERAPKSIGNER_H

#include <QStringList>
#include "macros.h"
#include "java.h"

APP_NAMESPACE_START

class UberApkSigner : public Java
{
private:
    QString _jar;
    static UberApkSigner *_self;
private:
    explicit UberApkSigner(QObject *parent = 0);
public:
    // Result build(const QString &project, const QString &apk);
    // Result decode(const QString &apk, const QString &project, const QString &framework, const bool sources, const bool resources);
    Result sign(const QString &src, const QString &keystore, const QString &keystorePass, const QString &key, const QString &keyPass = QString());
    Result signDebug(const QString &src);
    inline Result exec(const QString &arg) { return exec(QStringList(arg)); }
    Result exec(const QStringList &args = QStringList());
    static UberApkSigner *get();
    QString getVersion();
};

APP_NAMESPACE_END

#endif // UBERAPKSIGNER_H

