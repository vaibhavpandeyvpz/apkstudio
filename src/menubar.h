#ifndef MENUBAR_H
#define MENUBAR_H

#include "iaction.h"
#include "menubarui.h"

class MenuBar : public MenuBarUI
{
    Q_OBJECT
private:
    IAction *_iaction;
private Q_SLOTS:
    void onQuit();
    void onRestart();
public:
    MenuBar(QWidget *parent)
        : MenuBarUI(parent) {
    }
    ~MenuBar() {
    }
public:
    void bind(IAction *);
    void invalidate();
};

#endif // MENUBAR_H
