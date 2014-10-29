#include "ide.hpp"

using namespace VPZ::APKStudio::Components;

namespace VPZ {
namespace APKStudio {
namespace Windows {

IDE::IDE(QWidget *parent) :
    QMainWindow(parent), exit_code(0)
{
    devices = new Devices(this);
    editor = new Editor(this);
    files = new Files(this);
    menu_bar = new MenuBar(this);
    opened = new QStandardItemModel(this);
    outline = new Outline(this);
    output = new Output(this);
    projects = new Projects(this);
    tasks = new Tasks(this);
    status_bar = new QStatusBar(this);
    tool_bar = new ToolBar(this);
    editor->setModel(opened);
    files->setModel(opened);
    connections.append(connect(files, SIGNAL(selectionChanged(int)), editor, SLOT(onSelectionChanged(int))));
    connections.append(connect(editor, SIGNAL(selectionChanged(int)), files, SLOT(onSelectionChanged(int))));
    addToolBar(Qt::TopToolBarArea, tool_bar);
    setMenuBar(menu_bar);
    setCentralWidget(editor);
    setStatusBar(status_bar);
    setupDocks();
    foreach (const QString &extension, QString("java|png|smali|xml").split('|'))
        editor->open(QString("C:/Users/VPZ/Documents/apkstudio/sample/sample.").append(extension));
}

void IDE::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes != QMessageBox::question(this, translate("mbox_close_title"), translate("mbox_close_message"), QMessageBox::No | QMessageBox::Yes))
        return;
    bool maximized = isMaximized();
    Helpers::Settings::dockState(saveState());
    Helpers::Settings::maximized(maximized);
    if (!maximized)
        Helpers::Settings::windowSize(size());
    qApp->exit(exit_code);
}

void IDE::onActionAdbKill()
{
    Helpers::ADB::instance()->kill();
}

void IDE::onActionAdbStart()
{
    Helpers::ADB::instance()->start();
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

void IDE::onActionFirst()
{
    editor->first();
}

void IDE::onActionLast()
{
    editor->last();
}

void IDE::onActionNext()
{
    editor->next();
}

void IDE::onActionPrevious()
{
    editor->previous();
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

void IDE::onActionSettings()
{
    Settings *settings = new Settings(this);
    settings->open();
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
    restoreState(Helpers::Settings::dockState());
    setMinimumSize(QSize(800, 600));
    if (Helpers::Settings::maximized())
        showMaximized();
    else
        resize(Helpers::Settings::windowSize());
    setDockOptions(AnimatedDocks);
    setWindowTitle(translate("window_title"));
}

void IDE::onShowExplorer(const QString &device)
{
    Explorer *explorer = new Explorer(device, this);
    explorer->show();
}

void IDE::onShowInformation(const QString &device)
{
    Information *information = new Information(device, this);
    information->show();
}

void IDE::onShowLogcat(const QString &device)
{
    Logcat *logcat = new Logcat(device, this);
    logcat->show();
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
