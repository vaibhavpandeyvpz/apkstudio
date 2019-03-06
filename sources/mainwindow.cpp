#include <QCloseEvent>
#include <QDebug>
#include <QDesktopServices>
#include <QFrame>
#include <QMenuBar>
#include <QMessageBox>
#include <QSettings>
#include <QStatusBar>
#include <QToolBar>
#include <QUrl>
#include "binarysettingsdialog.h"
#include "binaryversionsthread.h"
#include "mainwindow.h"

#define URL_CONTRIBUTE "https://github.com/vaibhavpandeyvpz/apkstudio"
#define URL_DOCUMENTATION "https://vaibhavpandey.com/apkstudio/"
#define URL_ISSUES "https://github.com/vaibhavpandeyvpz/apkstudio/issues"
#define URL_THANKS "https://forum.xda-developers.com/showthread.php?t=2493107"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    addToolBar(Qt::LeftToolBarArea, buildMainToolBar());
    setMenuBar(buildMenuBar());
    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setStatusBar(buildStatusBar());
    setWindowTitle(tr("APK Studio").append(" - https://git.io/fhxGT"));
    QSettings settings;
    if (settings.value("app_maximized").toBool()) {
        showMaximized();
    } else {
        resize(settings.value("app_size", QSize(WINDOW_WIDTH, WINDOW_HEIGHT)).toSize());
    }
    auto thread = new BinaryVersionsThread();
    connect(thread, &BinaryVersionsThread::versionResolved, this, &MainWindow::handleVersionResolved);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    thread->start();
}

QToolBar *MainWindow::buildMainToolBar()
{
    auto toolbar = new QToolBar(this);
    toolbar->addAction(QIcon(":/icons/icons8/icons8-android-os-48.png"), tr("Open > APK"), this, &MainWindow::handleActionApk);
    toolbar->addAction(QIcon(":/icons/icons8/icons8-folder-48.png"), tr("Open > Folder"), this, &MainWindow::handleActionFolder);
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/icons/icons8/icons8-gear-48.png"), tr("Settings"), this, &MainWindow::handleActionSettings);
    auto empty = new QWidget(this);
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(empty);
    toolbar->addAction(QIcon(":/icons/icons8/icons8-hammer-48.png"), tr("Project > Build"), this, &MainWindow::handleActionBuild);
    toolbar->addAction(QIcon(":/icons/icons8/icons8-software-installer-48.png"), tr("Project > Install"), this, &MainWindow::handleActionInstall);
    toolbar->setIconSize(QSize(48, 48));
    toolbar->setMovable(false);
    return toolbar;
}

QMenuBar *MainWindow::buildMenuBar()
{
    auto menubar = new QMenuBar(this);
    auto file = menubar->addMenu(tr("File"));
    auto open = file->addMenu(tr("Open"));
    open->addAction(tr("APK"), this, &MainWindow::handleActionApk, QKeySequence::New);
    open->addAction(tr("Folder"), this, &MainWindow::handleActionFolder, QKeySequence::Open);
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

QStatusBar *MainWindow::buildStatusBar()
{
    auto buildSeparator = [=] {
        auto frame = new QFrame(this);
        frame->setFrameStyle(QFrame::VLine);
        frame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        return frame;
    };
    auto statusbar = new QStatusBar(this);
    statusbar->addPermanentWidget(new QLabel(tr("Java").append(':'), this));
    statusbar->addPermanentWidget(m_VersionJava = new QLabel("...", this));
    statusbar->addPermanentWidget(buildSeparator());
    statusbar->addPermanentWidget(new QLabel(tr("Apktool").append(':'), this));
    statusbar->addPermanentWidget(m_VersionApktool = new QLabel("...", this));
    statusbar->addPermanentWidget(buildSeparator());
    statusbar->addPermanentWidget(new QLabel(tr("Jadx").append(':'), this));
    statusbar->addPermanentWidget(m_VersionJadx = new QLabel("...", this));
    statusbar->addPermanentWidget(buildSeparator());
    statusbar->addPermanentWidget(new QLabel(tr("ADB").append(':'), this));
    statusbar->addPermanentWidget(m_VersionAdb = new QLabel("...", this));
    statusbar->addPermanentWidget(buildSeparator());
    statusbar->addPermanentWidget(new QLabel(tr("Uber APK Signer").append(':'), this));
    statusbar->addPermanentWidget(m_VersionUberApkSigner = new QLabel("...", this));
    statusbar->addPermanentWidget(new QWidget(this), 1);
    statusbar->addPermanentWidget(m_StatusMessage = new QLabel(tr("Ready!"), this));
    statusbar->setContentsMargins(4, 4, 4, 4);
    statusbar->setStyleSheet("QStatusBar::item { border: none; }");
    return statusbar;
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

void MainWindow::handleActionFolder()
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
    close();
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
    (new BinarySettingsDialog("java", this))->exec();
}

void MainWindow::handleActionSignExport()
{
}

void MainWindow::handleActionUndo()
{
}

void MainWindow::handleVersionResolved(const QString &binary, const QString &version)
{
#ifdef QT_DEBUG
    qDebug() << "Binary" << binary << "version resolved as" << version;
#endif
    if (binary == "adb") {
        m_VersionAdb->setText(version.isEmpty() ? tr("n/a") : version);
    } else if (binary == "apktool") {
        m_VersionApktool->setText(version.isEmpty() ? tr("n/a") : version);
    } else if (binary == "jadx") {
        m_VersionJadx->setText(version.isEmpty() ? tr("n/a") : version);
    } else if (binary == "java") {
        m_VersionJava->setText(version.isEmpty() ? tr("n/a") : version);
    } else if (binary == "uas") {
        m_VersionUberApkSigner->setText(version.isEmpty() ? tr("n/a") : version);
    }
}

MainWindow::~MainWindow()
{
}
