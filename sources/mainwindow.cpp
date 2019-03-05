#include <QCloseEvent>
#include <QDesktopServices>
#include <QMenuBar>
#include <QMessageBox>
#include <QSettings>
#include <QUrl>
#include "mainwindow.h"

#define URL_CONTRIBUTE "https://github.com/vaibhavpandeyvpz/apkstudio"
#define URL_DOCUMENTATION "https://vaibhavpandey.com/apkstudio"
#define URL_ISSUES "https://github.com/vaibhavpandeyvpz/apkstudio/issues"
#define URL_THANKS "https://forum.xda-developers.com/showthread.php?t=2493107"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMenuBar(buildMenuBar());
    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle(tr("APK Studio", "main").append(" - https://git.io/fhxGT"));
    QSettings settings;
    if (settings.value("app_maximized").toBool()) {
        showMaximized();
    } else {
        resize(settings.value("app_size", QSize(WINDOW_WIDTH, WINDOW_HEIGHT)).toSize());
    }
}

QMenuBar *MainWindow::buildMenuBar()
{
    auto menubar = new QMenuBar(this);
    auto file = menubar->addMenu(tr("File"));
    auto open = file->addMenu(tr("Open"));
    open->addAction(tr("APK"), this, &MainWindow::handleActionApk, QKeySequence::New);
    open->addAction(tr("Directory"), this, &MainWindow::handleActionDirectory, QKeySequence::Open);
    open->addSeparator();
    open->addAction(tr("File"), this, &MainWindow::handleActionFile);
    file->addSeparator();
    file->addAction(tr("Close"), this, &MainWindow::handleActionClose, QKeySequence::Close);
    file->addAction(tr("Close All"), this, &MainWindow::handleActionCloseAll);
    file->addSeparator();
    file->addAction(tr("Save"), this, &MainWindow::handleActionSave, QKeySequence::Save);
    file->addAction(tr("Save All"), this, &MainWindow::handleActionSaveAll);
    file->addSeparator();
    file->addAction(tr("Quit"), this, &MainWindow::handleActionQuit, QKeySequence::Quit);
    auto edit = menubar->addMenu(tr("Edit"));
    edit->addAction(tr("Undo"), this, &MainWindow::handleActionUndo, QKeySequence::Undo);
    edit->addAction(tr("Redo"), this, &MainWindow::handleActionRedo, QKeySequence::Redo);
    edit->addSeparator();
    edit->addAction(tr("Cut"), this, &MainWindow::handleActionCut, QKeySequence::Cut);
    edit->addAction(tr("Copy"), this, &MainWindow::handleActionCopy, QKeySequence::Copy);
    edit->addAction(tr("Paste"), this, &MainWindow::handleActionPaste, QKeySequence::Paste);
    edit->addSeparator();
    edit->addAction(tr("Find"), this, &MainWindow::handleActionFind, QKeySequence::Find);
    edit->addAction(tr("Replace"), this, &MainWindow::handleActionReplace, QKeySequence::Replace);
    edit->addAction(tr("Goto"), this, &MainWindow::handleActionGoto);
    edit->addSeparator();
    edit->addAction(tr("Settings"), this, &MainWindow::handleActionSettings, QKeySequence::Preferences);
    auto project = menubar->addMenu(tr("Project"));
    project->addAction(tr("Build"), this, &MainWindow::handleActionBuild);
    project->addSeparator();
    project->addAction(tr("Sign/Export"), this, &MainWindow::handleActionSignExport);
    project->addAction(tr("Install"), this, &MainWindow::handleActionInstall);
    auto help = menubar->addMenu(tr("Help"));
    help->addAction(tr("About"), this, &MainWindow::handleActionAbout);
    help->addAction(tr("Documentation"), this, &MainWindow::handleActionDocumentation);
    help->addSeparator();
    auto feedback = help->addMenu(tr("Feedback"));
    feedback->addAction(tr("Say Thanks"), this, &MainWindow::handleActionSayThanks);
    feedback->addAction(tr("Report Issues"), this, &MainWindow::handleActionReportIssues);
    help->addAction(tr("Contribute"), this, &MainWindow::handleActionContribute);
    return menubar;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    QSettings settings;
    bool maximized = isMaximized();
    settings.setValue("app_maximized", maximized);
    if (!maximized) {
        settings.setValue("app_size", size());
    }
    settings.sync();
}

void MainWindow::handleActionAbout()
{
}

void MainWindow::handleActionApk()
{
}

void MainWindow::handleActionBuild()
{
}

void MainWindow::handleActionClose()
{
}

void MainWindow::handleActionCloseAll()
{
}

void MainWindow::handleActionContribute()
{
    QDesktopServices::openUrl(QUrl(URL_CONTRIBUTE));
}

void MainWindow::handleActionCopy()
{
}

void MainWindow::handleActionCut()
{
}

void MainWindow::handleActionDirectory()
{
}

void MainWindow::handleActionDocumentation()
{
    QDesktopServices::openUrl(QUrl(URL_DOCUMENTATION));
}

void MainWindow::handleActionFile()
{
}

void MainWindow::handleActionFind()
{
}

void MainWindow::handleActionGoto()
{
}

void MainWindow::handleActionInstall()
{
}

void MainWindow::handleActionPaste()
{
}

void MainWindow::handleActionQuit()
{
}

void MainWindow::handleActionRedo()
{
}

void MainWindow::handleActionReplace()
{
}

void MainWindow::handleActionReportIssues()
{
    QDesktopServices::openUrl(QUrl(URL_ISSUES));
}

void MainWindow::handleActionSave()
{
}

void MainWindow::handleActionSaveAll()
{
}

void MainWindow::handleActionSayThanks()
{
    QDesktopServices::openUrl(QUrl(URL_THANKS));
}

void MainWindow::handleActionSettings()
{
}

void MainWindow::handleActionSignExport()
{
}

void MainWindow::handleActionUndo()
{
}

MainWindow::~MainWindow()
{
}
