#ifndef APKTOOL_H
#define APKTOOL_H

#include <QStringList>
#include "macros.h"
#include "java.h"

APP_NAMESPACE_START

class ApkTool : public Java
{
private:
    QString _jar;
    static ApkTool *_self;
private:
    explicit ApkTool(QObject *parent = 0);
public:
    Result build(const QString &project, const QString &apk);
    Result decode(const QString &apk, const QString &project, const QString &framework, const bool sources, const bool resources);
    inline Result exec(const QString &arg) { return exec(QStringList(arg)); }
    Result exec(const QStringList &args = QStringList());
    static ApkTool *get();
    QString getVersion();
};

APP_NAMESPACE_END

#endif // APKTOOL_H
