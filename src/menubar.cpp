#include "menubar.h"

void MenuBar::invalidate()
{
}

void MenuBar::bind(IAction *iaction)
{
    _iaction = iaction;
    // Bind: Children
    connect(_restart, SIGNAL(triggered()), this, SLOT(onRestart()));
    connect(_quit, SIGNAL(triggered()), this, SLOT(onQuit()));
}

void MenuBar::onQuit()
{
    _iaction->onActionQuit();
}

void MenuBar::onRestart()
{
    _iaction->onActionRestart();
}
