#ifndef PROCESSUTILS_H
#define PROCESSUTILS_H

#include <QStringList>

#define PROCESS_TIMEOUT_SECS 5 * 60

class ProcessUtils
{
public:
    struct ProcessResult {
        int code;
        QStringList error;
        QStringList output;
    };
    static QString adbExe();
    static QString apktoolJar();
    static QString expandEnvVar(const QString &name);
    static QString findInPath(const QString &exe);
    static QString jadxExe();
    static QString javaExe();
    static QString uberApkSignerJar();
    static ProcessResult runCommand(const QString &exe, const QStringList &args = QStringList(), const int timeout = PROCESS_TIMEOUT_SECS);
};

#endif // PROCESSUTILS_H
