#include "ideui.h"

void IDEUI::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes != QMessageBox::question(this, translate("mbox_close_title"), translate("mbox_close_message"), QMessageBox::No | QMessageBox::Yes))
        return;
    bool maximized = isMaximized();
    Settings::maximized(maximized);
    if (!maximized)
        Settings::windowSize(size());
    qApp->exit(_exit_code);
}

void IDEUI::prepare()
{
    // MenuBar
    _menubar = new MenuBar(this);
    _menubar->invalidate();
    setMenuBar(_menubar);
    // ToolBar
    _toolbar = new ToolBar(this);
    _toolbar->invalidate();
    addToolBar(Qt::TopToolBarArea, _toolbar);
    // Self
    _exit_code = 0;
}

void IDEUI::inflate()
{
    // Resize
    setMinimumSize(QSize(800, 600));
    if (Settings::maximized())
        showMaximized();
    else
        resize(Settings::windowSize());
    // Window
    setDockOptions(AllowTabbedDocks | AllowNestedDocks | AnimatedDocks);
    setWindowTitle(translate("window_title"));
}
