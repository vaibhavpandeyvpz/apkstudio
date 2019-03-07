#ifndef PROCESSUTILS_H
#define PROCESSUTILS_H

#include <QStringList>

struct ProcessResult {
    int code;
    QStringList error;
    QStringList output;
};

class ProcessUtils
{
public:
    static QString adbExe();
    static QString apktoolJar();
    static QString expandEnvVar(const QString &name);
    static QString findInPath(const QString &exe);
    static QString jadxExe();
    static QString javaExe();
    static QString uberApkSignerJar();
    static ProcessResult runCommand(const QString &exe, const QStringList &args = QStringList(), int timeout = 30);
};

#endif // PROCESSUTILS_H
