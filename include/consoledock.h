#ifndef CONSOLEDOCK_H
#define CONSOLEDOCK_H

#include <QDockWidget>
#include <QTextEdit>
#include "process.h"
#include "macros.h"

APP_NAMESPACE_START

class ConsoleDock : public QDockWidget
{
    Q_OBJECT
private:
    QTextEdit *_edit;
protected:
    APP_CONNECTIONS_LIST
public:
    explicit ConsoleDock(QWidget *parent = 0);
    ~ConsoleDock();
public Q_SLOTS:
    void onExecuted(const Process::Result &result);
    void onExecuting(const QString &command, const QStringList &args);
};

APP_NAMESPACE_END

#endif // CONSOLEDOCK_H
