#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "macros.h"

AS_NAMESPACE_START

class Dialog : public QDialog
{
    Q_OBJECT
protected:
    AS_CONNECTIONS_LIST
public:
    explicit Dialog(const QString &title, QWidget *parent = 0);
    ~Dialog();
};

AS_NAMESPACE_END

#endif // DIALOG_H
