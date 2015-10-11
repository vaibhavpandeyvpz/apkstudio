#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "macros.h"

APP_NAMESPACE_START

class Dialog : public QDialog
{
    Q_OBJECT
protected:
    APP_CONNECTIONS_LIST
public:
    explicit Dialog(const QString &title, QWidget *parent = 0);
    ~Dialog();
};

APP_NAMESPACE_END

#endif // DIALOG_H
