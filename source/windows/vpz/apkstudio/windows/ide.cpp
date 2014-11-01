#include "ide.hpp"

using namespace VPZ::APKStudio::Components;

namespace VPZ {
namespace APKStudio {
namespace Windows {

IDE::IDE(QWidget *parent) :
    QMainWindow(parent), exit_code(0)
{
    editing = new QStandardItemModel(this);
    devices = new Devices(this);
    editor = new Editor(editing, this);
    files = new Files(editing, this);
    menu_bar = new MenuBar(this);
    opened = new Helpers::Projects(this);
    outline = new Outline(this);
    output = new Output(this);
    projects = new Projects(opened, this);
    tasks = new Tasks(this);
    status_bar = new StatusBar(this);
    tool_bar = new ToolBar(this);
    connections.append(connect(files, SIGNAL(selectionChanged(int)), editor, SLOT(onSelectionChanged(int))));
    connections.append(connect(editor, SIGNAL(selectionChanged(int)), files, SLOT(onSelectionChanged(int))));
    connections.append(connect(projects, SIGNAL(editFile(QString)), this, SLOT(onEditFile(QString))));
    connections.append(connect(this, SIGNAL(viewToggled(const char *, bool)), menu_bar, SLOT(onViewToggled(const char *, bool))));
    addToolBar(Qt::TopToolBarArea, tool_bar);
    setCentralWidget(editor);
    setDocks();
    setMenuBar(menu_bar);
    setStatusBar(status_bar);
}

void IDE::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes != QMessageBox::question(this, translate("title_close"), translate("message_close"), QMessageBox::No | QMessageBox::Yes))
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

void IDE::onActionCloseFile()
{
    editor->close();
}

void IDE::onActionCloseProject()
{
    opened->close(projects->selected());
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

void IDE::onActionOpenApk()
{
    QFileDialog dialog(this, translate("title_open_apk"), Helpers::Settings::previousDirectory(), "Android APK (*.apk)");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec() != QFileDialog::Accepted)
        return;
    Helpers::Settings::previousDirectory(dialog.directory().absolutePath());
    QStringList files = dialog.selectedFiles();
    if (files.size() != 1)
        return;
}

void IDE::onActionOpenFile()
{
    QFileDialog dialog(this, translate("title_open_file"), Helpers::Settings::previousDirectory());
    QStringList filters("All supported formats (*.java;*.png;*.smali;*.xml;)");
    filters << "apktool (*.yml)";
    filters << "Images (*.png)";
    filters << "Java (Read-only) (*.java)";
    filters << "Dex smali (*.smali)";
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilters(filters);
    if (dialog.exec() != QFileDialog::Accepted)
        return;
    Helpers::Settings::previousDirectory(dialog.directory().absolutePath());
    QStringList files = dialog.selectedFiles();
    if (files.isEmpty())
        return;
    foreach (const QString &file, files)
        onEditFile(file);
}

void IDE::onActionOpenProject()
{
    QFileDialog dialog(this, translate("title_open_project"), Helpers::Settings::previousDirectory(), "apktool (*.yml)");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec() != QFileDialog::Accepted)
        return;
    Helpers::Settings::previousDirectory(dialog.directory().absolutePath());
    QStringList files = dialog.selectedFiles();
    if (files.size() != 1)
        return;
    opened->open(files.first());
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

void IDE::onActionSave()
{
    editor->save();
}

void IDE::onActionSaveAll()
{
    editor->save(true);
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

void IDE::onEditFile(const QString &path)
{
    editor->open(path);
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
    setWindowTitle(translate("title_window"));
}

void IDE::setDocks()
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

IDE::~IDE()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ
