#ifndef OUTPUTDOCK_H
#define OUTPUTDOCK_H

#include <QDockWidget>
#include <QTextEdit>
#include "adb.h"
#include "macros.h"

APP_NAMESPACE_START

class ConsoleDock : public QDockWidget
{
    Q_OBJECT
private:
    QString _binary;
    QTextEdit *_edit;
protected:
    AS_CONNECTIONS_LIST
public slots:
    void onExecuted(const Process::Result &result);
    void onExecuting(const QStringList &commands);
public:
    explicit ConsoleDock(const QString &title, const QString &binary, QWidget *parent = 0);
    ~ConsoleDock();
};

APP_NAMESPACE_END

#endif // OUTPUTDOCK_H
