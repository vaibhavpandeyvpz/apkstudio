#ifndef PROCESSUTILS_H
#define PROCESSUTILS_H

#include <QObject>
#include <QStringList>

#define PROCESS_TIMEOUT_SECS 5 * 60

struct ProcessResult {
    int code;
    QStringList error;
    QStringList output;
};

class ProcessOutput : public QObject
{
    Q_OBJECT
public:
    void emitCommandFinished(const ProcessResult &result);
    void emitCommandStarting(const QString &exe, const QStringList &args);
    static ProcessOutput *instance();
private:
    static ProcessOutput *m_Self;
signals:
    void commandFinished(const ProcessResult &result);
    void commandStarting(const QString &exe, const QStringList &args);
};

class ProcessUtils
{
public:
    static QString adbExe();
    static QString apktoolJar();
    static QString findInPath(const QString &exe);
    static QString jadxExe();
    static QString javaExe();
    static int javaHeapSize();
    static QString uberApkSignerJar();
    static ProcessResult runCommand(const QString &exe, const QStringList &args = QStringList(), const int timeout = PROCESS_TIMEOUT_SECS);
};

Q_DECLARE_METATYPE(ProcessResult);

#endif // PROCESSUTILS_H
