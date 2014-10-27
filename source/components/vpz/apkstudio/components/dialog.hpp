#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <QDialog>

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0)
        : QDialog(parent) {
        setAttribute(Qt::WA_DeleteOnClose, true);
    }
    inline void setDialogLayout(QLayout *layout) { setLayout(layout); }
};

#endif // DIALOG_HPP
