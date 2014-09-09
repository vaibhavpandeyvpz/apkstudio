#ifndef IDEUI_H
#define IDEUI_H

#include <QMainWindow>

class IDEUI : public QMainWindow
{
    Q_OBJECT
private:
    void inflate();
public:
    explicit IDEUI(QWidget *parent = 0)
        : QMainWindow(parent) {
        inflate();
    }
    ~IDEUI() {
    }
};

#endif // IDEUI_H
