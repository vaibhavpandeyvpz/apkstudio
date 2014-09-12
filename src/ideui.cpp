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
    // Panels
    _editors_panel = new EditorsPanel(this);
    _files_panel = new FilesPanel(this);
    _logs_panel = new LogsPanel(this);
    _outline_panel = new OutlinePanel(this);
    _projects_panel = new ProjectsPanel(this);
    _tasks_panel = new TasksPanel(this);
    addDockWidget(Qt::BottomDockWidgetArea, _logs_panel);
    addDockWidget(Qt::LeftDockWidgetArea, _projects_panel);
    addDockWidget(Qt::LeftDockWidgetArea, _files_panel);
    addDockWidget(Qt::RightDockWidgetArea, _outline_panel);
    addDockWidget(Qt::RightDockWidgetArea, _tasks_panel);
    setCentralWidget(_editors_panel);
    // StatusBar
    _statusbar = new QStatusBar(this);
    setStatusBar(_statusbar);
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
    setDockOptions(AnimatedDocks | AllowNestedDocks);
    setWindowTitle(translate("window_title"));
}
