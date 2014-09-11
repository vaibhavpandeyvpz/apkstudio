#ifndef IDE_H
#define IDE_H

#include "iaction.h"
#include "ideui.h"

class IDE : public IDEUI, public IAction
{
    Q_OBJECT
    Q_INTERFACES(IAction)
private:
    void attach();
public:
    IDE(QWidget *parent = 0)
        : IDEUI(parent) {
        attach();
    }
    ~IDE() {
    }
public Q_SLOTS:
    void onActionQuit();
    void onActionRestart();
};

#endif // IDE_H
