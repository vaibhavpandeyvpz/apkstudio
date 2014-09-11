#include "ide.h"

void IDE::attach()
{
    // Cast
    IAction *iaction = qobject_cast<IAction *>(this);
    // Attach
    _menubar->bind(iaction);
}

void IDE::onActionQuit()
{
    _exit_code = 0;
    close();
}

void IDE::onActionRestart()
{
    _exit_code = EXIT_CODE_RESTART;
    close();
}
