#ifndef SIGNINGCONFIGDIALOG_H
#define SIGNINGCONFIGDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include "signingconfigwidget.h"

class SigningConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SigningConfigDialog(QWidget *parent = nullptr);
private:
    QDialogButtonBox *m_ButtonBox;
    SigningConfigWidget *m_Widget;
    QWidget *buildButtonBox();
};

#endif // SIGNINGCONFIGDIALOG_H
