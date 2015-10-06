#ifndef PROCESS_H
#define PROCESS_H

#include <QRegularExpression>
#include <QStringList>
#include "macros.h"

AS_NAMESPACE_START

class Process : public QObject
{
    Q_OBJECT
private:
    QString _exe;
    QRegularExpression _lf;
public:
    explicit Process(const QString &exe, QObject *parent = 0);
public:
    struct Result
    {
        int code;
        QStringList error;
        QStringList output;
    };
public:
    inline Result exec(const QString &arg) { return exec(QStringList(arg)); }
    virtual Result exec(const QStringList &args = QStringList());
signals:
    void executed(Result);
    void executing(QStringList);
};

AS_NAMESPACE_END

Q_DECLARE_METATYPE(As::Process::Result)

#endif // PROCESS_H
