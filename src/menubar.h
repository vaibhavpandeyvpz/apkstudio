#ifndef MENUBAR_H
#define MENUBAR_H

#include "menubarui.h"

class MenuBar : public MenuBarUI
{
protected Q_SLOTS:
    void onRestart();
    void onQuit();
public:
    MenuBar(QWidget *parent)
        : MenuBarUI(parent) {
    }
    ~MenuBar() {
    }
public:
    void invalidate();
};

#endif // MENUBAR_H
