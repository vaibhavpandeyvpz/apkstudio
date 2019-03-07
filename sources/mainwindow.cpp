#include <QCloseEvent>
#include <QDebug>
#include <QDesktopServices>
#include <QDockWidget>
#include <QFileDialog>
#include <QFrame>
#include <QHeaderView>
#include <QMenuBar>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QStatusBar>
#include <QThread>
#include <QToolBar>
#include <QTreeWidgetItem>
#include <QUrl>
#include "apkdecompiledialog.h"
#include "apkdecompileworker.h"
#include "binarysettingsdialog.h"
#include "versionresolveworker.h"
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
    addDockWidget(Qt::LeftDockWidgetArea, buildProjectsDock());
    addToolBar(Qt::LeftToolBarArea, buildMainToolBar());
    setCentralWidget(buildCentralWidget());
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
    auto thread = new QThread();
    auto resolve = new VersionResolveWorker();
    resolve->moveToThread(thread);
    connect(thread, &QThread::started, resolve, &VersionResolveWorker::resolve);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(resolve, &VersionResolveWorker::versionResolved, this, &MainWindow::handleVersionResolved);
    thread->start();
}

QWidget *MainWindow::buildCentralWidget()
{
    m_CentralStack = new QStackedWidget(this);
    auto empty = new QLabel(m_CentralStack);
    empty->setAlignment(Qt::AlignCenter);
    empty->setMargin(32);
    empty->setStyleSheet("QLabel { color: rgba(0, 0, 0, 25%) }");
    empty->setText(tr("<h1>%1</h1><p>%2</p>")
                .arg("No files open.")
                .arg("You need to decompile an APK first or open an already decompiled folder. Once done, click on any file in the tree on the left top view or edit it."));
    empty->setWordWrap(true);
    m_CentralStack->addWidget(empty);
    return m_CentralStack;
}

QToolBar *MainWindow::buildMainToolBar()
{
    auto toolbar = new QToolBar(this);
    toolbar->addAction(QIcon(":/icons/icons8/icons8-android-os-48.png"), tr("Open APK"), this, &MainWindow::handleActionApk);
    toolbar->addAction(QIcon(":/icons/icons8/icons8-folder-48.png"), tr("Open Folder"), this, &MainWindow::handleActionFolder);
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/icons/icons8/icons8-gear-48.png"), tr("Settings"), this, &MainWindow::handleActionSettings);
    auto empty = new QWidget(this);
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(empty);
    m_ActionBuild2 = toolbar->addAction(QIcon(":/icons/icons8/icons8-hammer-48.png"), tr("Project Build"), this, &MainWindow::handleActionBuild);
    m_ActionBuild2->setEnabled(false);
    m_ActionInstall2 = toolbar->addAction(QIcon(":/icons/icons8/icons8-software-installer-48.png"), tr("Project Install"), this, &MainWindow::handleActionInstall);
    m_ActionInstall2->setEnabled(false);
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
    m_ActionClose = file->addAction(tr("Close"), this, &MainWindow::handleActionClose, QKeySequence::Close);
    m_ActionClose->setEnabled(false);
    m_ActionCloseAll = file->addAction(tr("Close All"), this, &MainWindow::handleActionCloseAll);
    m_ActionCloseAll->setEnabled(false);
    file->addSeparator();
    m_ActionSave = file->addAction(tr("Save"), this, &MainWindow::handleActionSave, QKeySequence::Save);
    m_ActionSave->setEnabled(false);
    m_ActionSaveAll = file->addAction(tr("Save All"), this, &MainWindow::handleActionSaveAll);
    m_ActionSaveAll->setEnabled(false);
    file->addSeparator();
    file->addAction(tr("Quit"), this, &MainWindow::handleActionQuit, QKeySequence::Quit);
    auto edit = menubar->addMenu(tr("Edit"));
    m_ActionUndo = edit->addAction(tr("Undo"), this, &MainWindow::handleActionUndo, QKeySequence::Undo);
    m_ActionUndo->setEnabled(false);
    m_ActionRedo = edit->addAction(tr("Redo"), this, &MainWindow::handleActionRedo, QKeySequence::Redo);
    m_ActionRedo->setEnabled(false);
    edit->addSeparator();
    m_ActionCut = edit->addAction(tr("Cut"), this, &MainWindow::handleActionCut, QKeySequence::Cut);
    m_ActionCut->setEnabled(false);
    m_ActionCopy = edit->addAction(tr("Copy"), this, &MainWindow::handleActionCopy, QKeySequence::Copy);
    m_ActionCopy->setEnabled(false);
    m_ActionPaste = edit->addAction(tr("Paste"), this, &MainWindow::handleActionPaste, QKeySequence::Paste);
    m_ActionPaste->setEnabled(false);
    edit->addSeparator();
    m_ActionFind = edit->addAction(tr("Find"), this, &MainWindow::handleActionFind, QKeySequence::Find);
    m_ActionFind->setEnabled(false);
    m_ActionReplace = edit->addAction(tr("Replace"), this, &MainWindow::handleActionReplace, QKeySequence::Replace);
    m_ActionReplace->setEnabled(false);
    m_ActionGoto = edit->addAction(tr("Goto"), this, &MainWindow::handleActionGoto);
    m_ActionGoto->setEnabled(false);
    edit->addSeparator();
    edit->addAction(tr("Settings"), this, &MainWindow::handleActionSettings, QKeySequence::Preferences);
    auto project = menubar->addMenu(tr("Project"));
    m_ActionBuild1 = project->addAction(tr("Build"), this, &MainWindow::handleActionBuild);
    m_ActionBuild1->setEnabled(false);
    project->addSeparator();
    m_ActionSign = project->addAction(tr("Sign/Export"), this, &MainWindow::handleActionSignExport);
    m_ActionSign->setEnabled(false);
    m_ActionInstall1 = project->addAction(tr("Install"), this, &MainWindow::handleActionInstall);
    m_ActionInstall1->setEnabled(false);
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

QDockWidget *MainWindow::buildProjectsDock()
{
    auto dock = new QDockWidget(tr("Projects"), this);
    m_ProjectsTree = new QTreeWidget(this);
    m_ProjectsTree->header()->hide();
    m_ProjectsTree->setContextMenuPolicy(Qt::CustomContextMenu);
    m_ProjectsTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_ProjectsTree->setMinimumWidth(240);
    m_ProjectsTree->setSelectionBehavior(QAbstractItemView::SelectItems);
    m_ProjectsTree->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ProjectsTree->setSortingEnabled(false);
    connect(m_ProjectsTree, &QTreeWidget::customContextMenuRequested, this, &MainWindow::handleTreeContextMenu);
    connect(m_ProjectsTree, &QTreeWidget::doubleClicked, this, &MainWindow::handleTreeDoubleClicked);
    dock->setObjectName("ProjectsDock");
    dock->setWidget(m_ProjectsTree);
    return dock;
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
    const QString path = QFileDialog::getOpenFileName(this,
                                                      tr("Browse APK"),
                                                      QString(),
                                                      tr("Android APK File(s) (*.apk)"));
#ifdef QT_DEBUG
    qDebug() << "User selected to open" << path;
#endif
    if (!path.isEmpty()) {
        auto dialog = new ApkDecompileDialog(QDir::toNativeSeparators(path), this);
        if (dialog->exec() == QDialog::Accepted) {
            auto thread = new QThread();
            auto decompile = new ApkDecompileWorker(dialog->apk(), dialog->folder(), dialog->sources());
            decompile->moveToThread(thread);
            connect(thread, &QThread::started, decompile, &ApkDecompileWorker::decompile);
            connect(thread, &QThread::finished, thread, &QObject::deleteLater);
            connect(decompile, &ApkDecompileWorker::decompileFailed, this, &MainWindow::handleDecompileFailed);
            connect(decompile, &ApkDecompileWorker::decompileFinished, this, &MainWindow::handleDecompileFinished);
            connect(decompile, &ApkDecompileWorker::decompileProgress, this, &MainWindow::handleDecompileProgress);
            thread->start();
            m_ProgressDialog = new QProgressDialog(this);
            m_ProgressDialog->setCancelButton(nullptr);
            m_ProgressDialog->setRange(0, 100);
            m_ProgressDialog->setWindowFlags(m_ProgressDialog->windowFlags() & ~Qt::WindowCloseButtonHint);
            m_ProgressDialog->setWindowTitle(tr("Decompiling..."));
            m_ProgressDialog->exec();
        }
        dialog->deleteLater();
    }
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
    const QString path = QFileDialog::getOpenFileName(this,
                                                      tr("Browse File"),
                                                      QString());
#ifdef QT_DEBUG
    qDebug() << "User selected to open" << path;
#endif
    if (!path.isEmpty()) {
        openFile(path);
    }
}

void MainWindow::handleActionFind()
{
}

void MainWindow::handleActionFolder()
{
    const QString path = QFileDialog::getOpenFileName(this,
                                                      tr("Browse Folder (apktool.yml)"),
                                                      QString(),
                                                      tr("Apktool Project File(s) (apktool.yml)"));
#ifdef QT_DEBUG
    qDebug() << "User selected to open" << path;
#endif
    if (!path.isEmpty()) {
        openProject(QFileInfo(path).dir().absolutePath());
    }
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

void MainWindow::handleDecompileFailed(const QString &apk)
{
    Q_UNUSED(apk)
    m_ProgressDialog->close();
    m_ProgressDialog->deleteLater();
    m_StatusMessage->setText(tr("Decompilation failed."));
}

void MainWindow::handleDecompileFinished(const QString &apk, const QString &folder)
{
    Q_UNUSED(apk)
    m_ProgressDialog->close();
    m_ProgressDialog->deleteLater();
    m_StatusMessage->setText(tr("Decompilation finished."));
    openProject(folder);
}

void MainWindow::handleDecompileProgress(const int percent, const QString &message)
{
    m_ProgressDialog->setLabelText(message);
    m_ProgressDialog->setValue(percent);
}

void MainWindow::handleTreeContextMenu(const QPoint &point)
{
    auto item = m_ProjectsTree->itemAt(point);
    const int type = item->data(0, Qt::UserRole + 1).toInt();
    const QString path = item->data(0, Qt::UserRole + 2).toString();
#ifdef QT_DEBUG
    qDebug() << "Content menu requested for" << item->text(0) << "at" << point;
#endif
    QMenu menu(this);
    QAction *open = menu.addAction(tr("Open"));
    if (type != File) {
        open->setEnabled(false);
    } else {
        connect(open, &QAction::triggered, [=] {
            openFile(path);
        });
    }
#ifdef Q_OS_WIN
    QAction *openin = menu.addAction(tr("Open in Explorer"));
    connect(openin, &QAction::triggered, [=] {
        QStringList args;
        if (type == File) {
            args << QLatin1String("/select,");
        }
        args << QDir::toNativeSeparators(path);
        QProcess::startDetached("explorer.exe", args);
    });
#elif defined(Q_OS_MACOS)
    QAction *openin = menu.addAction(tr("Open in Finder"));
    connect(openin, &QAction::triggered, [=] {
        QStringList args;
        args << "-e" << QString("tell application \"Finder\" to reveal POSIX file \"%1\"").arg(path);
        QProcess::execute("/usr/bin/osascript", args);
        args.clear();
        args << "-e" << "tell application \"Finder\" to activate";
        QProcess::execute("/usr/bin/osascript", args);
    });
#else
    QAction *openin = menu.addAction(tr("Open in Files"));
    connect(openin, &QAction::triggered, [=] {
        QProcess::startDetached("xdg-open", QStringList() << path);
    });
#endif
    menu.addSeparator();
    QAction *collapse = menu.addAction(tr("Collapse All"));
    connect(collapse, &QAction::triggered, m_ProjectsTree, &QTreeWidget::collapseAll);
    menu.exec(m_ProjectsTree->mapToGlobal(point));
}

void MainWindow::handleTreeDoubleClicked(const QModelIndex &index)
{
    const int type = index.data(Qt::UserRole + 1).toInt();
    const QString path = index.data(Qt::UserRole + 2).toString();
#ifdef QT_DEBUG
    qDebug() << "User double clicked" << path;
#endif
    switch (type) {
    case Project:
    case Folder:
        break;
    case File:
        openFile(path);
        break;
    }
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

void MainWindow::openFile(const QString &path)
{
#ifdef QT_DEBUG
    qDebug() << "Opening" << path;
#endif
}

void MainWindow::openProject(const QString &folder)
{
    QFileInfo info(folder);
    QTreeWidgetItem *item = new QTreeWidgetItem(m_ProjectsTree);
    item->setData(0, Qt::UserRole + 1, Project);
    item->setData(0, Qt::UserRole + 2, folder);
    item->setIcon(0, m_FileIconProvider.icon(info));
    item->setText(0, info.fileName());
    reloadChildren(item);
    m_ProjectsTree->addTopLevelItem(item);
    m_ProjectsTree->expandItem(item);
    m_ActionBuild1->setEnabled(true);
    m_ActionBuild2->setEnabled(true);
}

void MainWindow::reloadChildren(QTreeWidgetItem *item)
{
    while (item->childCount()) {
        qDeleteAll(item->takeChildren());
    }
    QDir dir(item->data(0, Qt::UserRole + 2).toString());
    if (dir.exists()) {
        QFileInfoList files = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst);
        foreach (QFileInfo info, files) {
            QTreeWidgetItem *child = new QTreeWidgetItem(item);
            child->setData(0, Qt::UserRole + 1, info.isDir() ? Folder : File);
            child->setData(0, Qt::UserRole + 2, info.absoluteFilePath());
            child->setIcon(0, m_FileIconProvider.icon(info));
            child->setText(0, info.fileName());
            item->addChild(child);
            if (info.isDir()) {
                reloadChildren(child);
            }
        }
    }
}

MainWindow::~MainWindow()
{
}
