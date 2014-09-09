#ifndef IDE_H
#define IDE_H

#include <QApplication>

#include "ideui.h"

class IDE : public IDEUI
{
    Q_OBJECT
public:
    IDE(QWidget *parent = 0)
        : IDEUI(parent) {
    }
    ~IDE() {
    }
};

#endif // IDE_H
