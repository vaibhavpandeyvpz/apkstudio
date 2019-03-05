#ifndef BINARYSETTINGSDIALOG_H
#define BINARYSETTINGSDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include "binarysettingswidget.h"

class BinarySettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BinarySettingsDialog(const QString &focus, QWidget *parent = nullptr);
private:
    QDialogButtonBox *m_ButtonBox;
    BinarySettingsWidget *m_Widget;
    QWidget *buildButtonBox();
private slots:
    void handleButtonClick(QAbstractButton *button);
};

#endif // BINARYSETTINGSDIALOG_H
