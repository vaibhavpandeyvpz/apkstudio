#ifndef APKTOOL_H
#define APKTOOL_H

#include <QStringList>
#include "macros.h"
#include "java.h"

AS_NAMESPACE_START

class ApkTool : public Java
{
private:
    static ApkTool *_self;
    QString _jar;
private:
    explicit ApkTool(QObject *parent = 0);
public:
    Result build(const QString &src, const QString &dest);
    Result decode(const QString &src, const QString &dest);
    inline Result exec(const QString &arg) { return exec(QStringList(arg)); }
    Result exec(const QStringList &args = QStringList());
    static ApkTool *get();
    QString getVersion();
};

AS_NAMESPACE_END

#endif // APKTOOL_H
