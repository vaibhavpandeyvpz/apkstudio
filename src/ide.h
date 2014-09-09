#ifndef IDE_H
#define IDE_H

#include <QApplication>
#include <QMainWindow>

class IDE : public QMainWindow
{
    Q_OBJECT

public:
    IDE(QWidget *parent = 0);
    ~IDE();
};

#endif // IDE_H
