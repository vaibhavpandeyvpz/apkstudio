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
    static QString apktoolJar();
    static QString javaExe();
    static QString jadxExe();
    static ProcessResult runCommand(const QString &exe, const QStringList &args = QStringList(), int timeout = 30);
};

#endif // PROCESSUTILS_H
