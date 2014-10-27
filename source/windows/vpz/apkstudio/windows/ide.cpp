#include "ide.hpp"

using namespace VPZ::APKStudio::Components;
using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Windows {

IDE::IDE(QWidget *parent) :
    QMainWindow(parent), exit_code(0)
{
    devices = new Components::Devices(this);
    editor = new Components::Editor(this);
    files = new Components::Files(this);
    menu_bar = new MenuBar(this);
    outline = new Components::Outline(this);
    output = new Components::Output(this);
    projects = new Components::Projects(this);
    tasks = new Components::Tasks(this);
    status_bar = new QStatusBar(this);
    tool_bar = new ToolBar(this);
    addToolBar(Qt::TopToolBarArea, tool_bar);
    setMenuBar(menu_bar);
    setCentralWidget(editor);
    setStatusBar(status_bar);
    setupDocks();
}

void IDE::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes != QMessageBox::question(this, translate("mbox_close_title"), translate("mbox_close_message"), QMessageBox::No | QMessageBox::Yes))
        return;
    bool maximized = isMaximized();
    Settings::dockState(saveState());
    Settings::maximized(maximized);
    if (!maximized)
        Settings::windowSize(size());
    qApp->exit(exit_code);
}

void IDE::onActionAdbKill()
{
    ADB::instance()->kill();
}

void IDE::onActionAdbStart()
{
    ADB::instance()->start();
}

void IDE::onActionContribute()
{
    QDesktopServices::openUrl(QUrl(URL_CONTRIBUTE));
}

void IDE::onActionDonate()
{
    QDesktopServices::openUrl(QUrl(URL_DONATE));
}

void IDE::onActionFeedbackIssues()
{
    QDesktopServices::openUrl(QUrl(URL_ISSUES));
}

void IDE::onActionFeedbackThanks()
{
    QDesktopServices::openUrl(QUrl(URL_THANKS));
}

void IDE::onActionQuit()
{
    exit_code = 0;
    close();
}

void IDE::onActionRestart()
{
    exit_code = EXIT_CODE_RESTART;
    close();
}

void IDE::onActionToggle(QAction *toggle)
{
    QString name = toggle->objectName();
    if (name == "views_devices")
        devices->setVisible(toggle->isChecked());
    else if (name == "views_files")
        files->setVisible(toggle->isChecked());
    else if (name == "views_outline")
        outline->setVisible(toggle->isChecked());
    else if (name == "views_output")
        output->setVisible(toggle->isChecked());
    else if (name == "views_projects")
        projects->setVisible(toggle->isChecked());
    else if (name == "views_tasks")
        tasks->setVisible(toggle->isChecked());
}

void IDE::onInitComplete()
{
    restoreState(Settings::dockState());
    setMinimumSize(QSize(800, 600));
    if (Settings::maximized())
        showMaximized();
    else
        resize(Settings::windowSize());
    setDockOptions(AnimatedDocks);
    setWindowTitle(translate("window_title"));
}

void IDE::setupDocks()
{
    addDockWidget(Qt::BottomDockWidgetArea, output);
    addDockWidget(Qt::LeftDockWidgetArea, projects);
    addDockWidget(Qt::LeftDockWidgetArea, files);
    addDockWidget(Qt::RightDockWidgetArea, outline);
    addDockWidget(Qt::RightDockWidgetArea, tasks);
    addDockWidget(Qt::RightDockWidgetArea, devices);
    connections.append(connect(devices, &QDockWidget::visibilityChanged, [ this ] (bool visible) {
        emit viewToggled("views_devices", visible);
    }));
    connections.append(connect(files, &QDockWidget::visibilityChanged, [ this ] (bool visible) {
        emit viewToggled("views_files", visible);
    }));
    connections.append(connect(output, &QDockWidget::visibilityChanged, [ this ] (bool visible) {
        emit viewToggled("views_output", visible);
    }));
    connections.append(connect(outline, &QDockWidget::visibilityChanged, [ this ] (bool visible) {
        emit viewToggled("views_outline", visible);
    }));
    connections.append(connect(projects, &QDockWidget::visibilityChanged, [ this ] (bool visible) {
        emit viewToggled("views_projects", visible);
    }));
    connections.append(connect(tasks, &QDockWidget::visibilityChanged, [ this ] (bool visible) {
        emit viewToggled("views_tasks", visible);
    }));
}

IDE::~IDE()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ
