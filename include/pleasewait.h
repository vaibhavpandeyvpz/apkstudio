#ifndef PLEASEWAIT_H
#define PLEASEWAIT_H

#include <QCloseEvent>
#include <QKeyEvent>
#include "include/dialog.h"

APP_NAMESPACE_START

class PleaseWait : public Dialog
{
private:
    bool _finished;
protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
public:
    explicit PleaseWait(QWidget *parent = 0);
public:
    void finish();
};

APP_NAMESPACE_END

#endif // PLEASEWAIT_H
