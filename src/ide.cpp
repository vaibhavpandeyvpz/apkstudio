#include <QCloseEvent>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <QMimeData>
#include <QProcess>
#include <QProgressBar>
#include <QTimer>
#include "include/buildrunnable.h"
#include "include/constants.h"
#include "include/editortabs.h"
#include "include/decoderunnable.h"
#include "include/ide.h"
#include "include/fileutils.h"
#include "include/installrunnable.h"
#include "include/menubar.h"
#include "include/pathutils.h"
#include "include/pleasewait.h"
#include "include/preferences.h"
#include "include/preopenapk.h"
#include "include/process.h"
#include "include/qrc.h"
#include "include/runner.h"
#include "include/settingseditor.h"
#include "include/signexportapk.h"
#include "include/signrunnable.h"
#include "include/statusbar.h"
#include "include/textutils.h"
#include "include/toolbar.h"
#include "include/widgetbar.h"

APP_NAMESPACE_START

Ide::Ide(QWidget *parent)
    : QMainWindow(parent)
{
    _signed = false;
    addToolBar(Qt::TopToolBarArea, new ToolBar(this));
    setAcceptDrops(true);
    setCentralWidget(new EditorTabs(this));
    setDockOptions(AllowTabbedDocks | AnimatedDocks);
    setMenuBar(new MenuBar(this));
    setMinimumSize(800, 600);
    setStatusBar(_statusBar = new StatusBar(this));
    setWindowIcon(QIcon(Qrc::image("logo")));
    setWindowTitle(__("ide", "titles"));
    // Docks : Begin
    QDockWidget *console;
    QDockWidget *project;
    addDockWidget(Qt::BottomDockWidgetArea, console = new ConsoleDock(this));
    addDockWidget(Qt::LeftDockWidgetArea, project = new ProjectDock(this));
    // Docks : End
    // Widgets : Begin
    WidgetBar *bottom = new WidgetBar(this);
    WidgetBar *left = new WidgetBar(this);
    bottom->addWidget(Qrc::icon("dock_console"), console);
    bottom->setObjectName("BottomWidgetBar");
    left->addWidget(Qrc::icon("dock_project"), project);
    left->setObjectName("LeftWidgetBar");
    addToolBar(Qt::BottomToolBarArea, bottom);
    addToolBar(Qt::LeftToolBarArea, left);
    // Widgets : End
}

void Ide::closeEvent(QCloseEvent *e)
{
    QMessageBox mb(QMessageBox::Question, __("quit", "titles"), __("quit", "messages"));
    mb.addButton(QMessageBox::Yes);
    mb.addButton(QMessageBox::No);
    mb.setWindowIcon(Qrc::icon("dialog_quit"));
    if (QMessageBox::Yes == mb.exec())
    {
        Preferences *p = Preferences::get();
        bool m = isMaximized();
        p->setWindowMaximized(m);
        if (!m)
        {
            p->setWindowSize(size());
        }
        p->setDocksState(saveState());
        p->save();
    }
    else
    {
        e->ignore();
    }
}

void Ide::dropEvent(QDropEvent *e)
{
    bool accepted = false;
    const QMimeData* data = e->mimeData();
    if (data->hasUrls())
    {
        QList<QUrl> urls = data->urls();
        for (int i = 0; i < urls.size(); i++)
        {
            QString p = urls.at(i).toLocalFile();
            QString suffix = QFileInfo(p).suffix();
            if (QString::compare(suffix, "apk", Qt::CaseInsensitive) == 0)
            {
                onOpenApk(p);
                accepted = true;
                break;
            }
            else if (QString(EDITOR_EXT_CODER).contains(suffix, Qt::CaseInsensitive) || QString(EDITOR_EXT_VIEWER).contains(suffix, Qt::CaseInsensitive))
            {
                onFileOpen(p);
                accepted = true;
            }
        }
    }
    if (accepted)
    {
        e->acceptProposedAction();
    }
}

void Ide::onBuildFailure(const QString &p)
{
    _statusBar->showMessage(__("build_failure", "messages", p));
}

void Ide::onBuildSuccess(const QString &a)
{
    _apk = a;
    _statusBar->showMessage(__("build_success", "messages", a));
}

void Ide::onDecodeFailure(const QString &a)
{
    _statusBar->showMessage(__("decode_failure", "messages", a));
}

void Ide::onDecodeSuccess(const QString &p)
{
    onOpenDir(p);
    _statusBar->showMessage(__("decode_success", "messages", p));
}

void Ide::onFileChanged(const QString &p)
{
    if (p.isEmpty())
    { setWindowTitle(__("ide", "titles")); }
    else
    { setWindowTitle(__("ide_alt", "titles", QFileInfo(p).fileName())); }
}

void Ide::onFileOpen(const QString &p)
{
    emit fileOpen(p);
}

void Ide::onFileSaved(const QString &p)
{
    _statusBar->showMessage(__("file_saved", "messages", p));
}

void Ide::onInit()
{
    Preferences *p = Preferences::get();
    if (p->wasWindowMaximized())
    {
        showMaximized();
    }
    else
    {
        resize(p->windowSize());
    }
    restoreState(p->docksState());
    if (!QFile::exists(PathUtils::combine(p->vendorPath(), "apktool.jar")) || !QFile::exists(PathUtils::combine(p->vendorPath(), "uber-apk-signer.jar")))
    {
        QMessageBox::warning(this, __("action_required", "titles"), __("download_vendor", "messages"), QMessageBox::Close);
    }
    QStringList f = p->sessionFiles();
    foreach (QString p, f)
    {
        if (QFile::exists(p))
        {
            emit fileOpen(p);
        }
    }
    QDir dir(Preferences::get()->sessionProject());
    if (dir.exists() && dir.exists("apktool.yml"))
    {
        emit onOpenDir(dir.absolutePath());
    }
}

void Ide::onInstallFailure(const QString &a)
{
    _statusBar->showMessage(__("install_failure", "messages", a));
}

void Ide::onInstallSuccess(const QString &a)
{
    _statusBar->showMessage(__("install_success", "messages", a));
}

void Ide::onMenuBarEditSettings()
{
    (new SettingsEditor(this))->exec();
}

void Ide::onMenuBarFileOpenApk()
{
    QFileDialog d(this, __("choose_apk", "titles"), Preferences::get()->previousDir(), __("apk", "filters"));
    d.setAcceptMode(QFileDialog::AcceptOpen);
    d.setFileMode(QFileDialog::ExistingFile);
#ifdef NO_NATIVE_DIALOG
    d.setOption(QFileDialog::DontUseNativeDialog);
#endif
    if (d.exec() == QFileDialog::Accepted)
    {
        QStringList files;
        if ((files = d.selectedFiles()).isEmpty() == false)
        {
            QDir dir = d.directory();
            Preferences::get()->setPreviousDir(dir.absolutePath())->save();
            onOpenApk(files.first());
        }
    }
}

void Ide::onMenuBarFileOpenDir()
{
    QFileDialog d(this, __("choose_exiting_project", "titles"), Preferences::get()->previousDir(), __("apktool_yml", "filters"));
    d.setAcceptMode(QFileDialog::AcceptOpen);
    d.setFileMode(QFileDialog::ExistingFile);
#ifdef NO_NATIVE_DIALOG
    d.setOption(QFileDialog::DontUseNativeDialog);
#endif
    if (d.exec() == QFileDialog::Accepted)
    {
        QStringList files;
        if ((files = d.selectedFiles()).isEmpty() == false)
        {
            QString dir = d.directory().absolutePath();
            Preferences::get()->setPreviousDir(dir)->save();
            onOpenDir(dir);
        }
    }
}

void Ide::onMenuBarFileOpenFile()
{
    QFileDialog d(this, __("choose_editable_files", "titles"), Preferences::get()->previousDir(), __("editable", "filters"));
    d.setAcceptMode(QFileDialog::AcceptOpen);
    d.setFileMode(QFileDialog::ExistingFiles);
#ifdef NO_NATIVE_DIALOG
    d.setOption(QFileDialog::DontUseNativeDialog);
#endif
    if (d.exec() == QFileDialog::Accepted)
    {
        QStringList files;
        if ((files = d.selectedFiles()).isEmpty() == false)
        {
            Preferences::get()->setPreviousDir(d.directory().absolutePath())->save();
            foreach (const QString &f, files)
            {
                emit fileOpen(f);
            }
        }
    }
}

void Ide::onMenuBarFileTerminal()
{
    QStringList a;
    QString wd;
    if (!_project.isNull() && !_project.isEmpty())
    { wd = _project; }
    else
    { wd = Preferences::get()->vendorPath(); }
#ifdef Q_OS_WIN
    QString c("cmd.exe");
    a << "/k" << QString("cd /d %1").arg(wd);
#else
    QString c("gnome-terminal");
    a << QString("--working-directory=").append(wd);
#endif
    QProcess::startDetached(c, a);
}

void Ide::onMenuBarHelpAbout()
{
    QMessageBox box;
    box.setIconPixmap(Qrc::image("logo"));
    box.setInformativeText(FileUtils::read(QString(QRC_HTML).arg("about")));
    box.setText(__("app_version", "messages"));
    box.setWindowIcon(Qrc::icon("dialog_about"));
    box.setWindowTitle(__("about", "titles"));
    box.exec();
}

void Ide::onMenuBarHelpContribute()
{
    QDesktopServices::openUrl(QUrl(URL_CONTRIBUTE));
}

void Ide::onMenuBarHelpDocumentation()
{
    QDesktopServices::openUrl(QUrl(URL_DOCUMENTATION));
}

void Ide::onMenuBarHelpFeedbackIssues()
{
    QDesktopServices::openUrl(QUrl(URL_ISSUES));
}

void Ide::onMenuBarHelpFeedbackThanks()
{
    QDesktopServices::openUrl(QUrl(URL_THANKS));
}

void Ide::onMenuBarProjectBuild()
{
    _signed = false;
    //save all opened files before building
    emit fileSaveAll();

    if (_project.isNull() || _project.isEmpty())
    {
        QMessageBox::warning(this, __("no_project", "titles"), __("no_project", "messages"), QMessageBox::Close);
    }
    else
    {
        Runner::get()->add(new BuildRunnable(_project, TextUtils::rtrim(_project, '/') + ".apk", this));
    }
}

void Ide::onMenuBarProjectInstall()
{

    if (_apk.isNull() || _apk.isEmpty())
    {
        QMessageBox::warning(this, __("no_apk", "titles"), __("no_apk", "messages"), QMessageBox::Close);
    }else if (!_signed)
    {
        QMessageBox::warning(this, __("not_signed", "titles"), __("not_signed", "messages"), QMessageBox::Close);
    }
    else
    {
        Runner::get()->add(new InstallRunnable(_apk, this));
    }
}

void Ide::onMenuBarProjectReload()
{
    emit projectReload();
}

void Ide::onMenuBarProjectSignExport()
{

    if (_apk.isNull() || _apk.isEmpty())
    {
        QMessageBox::warning(this, __("no_apk", "titles"), __("no_apk", "messages"), QMessageBox::Close);
    }
    else
    {
        SignExportApk *s = new SignExportApk(this);
        if (s->exec() == Dialog::Accepted)
        {
            Runner::get()->add(new SignRunnable(_apk, s->keystore(), s->keystorePass(), s->key(), s->keyPass(), this));
        }
        delete s;
    }
}

void Ide::onMenuBarProjectBrowseFiles()
{

    FileUtils::show(_project + "/");
}

void Ide::onToolBarProjectSign()
{

    if (_apk.isNull() || _apk.isEmpty())
    {
        QMessageBox::warning(this, __("no_apk", "titles"), __("no_apk", "messages"), QMessageBox::Close);
    }
    else
    {
        Preferences *p = Preferences::get();
        Runner::get()->add(new SignRunnable(_apk, p->signKeystore(), p->signKeystorePass(), p->signKey(), p->signKeyPass(), this));
    }
}

void Ide::onOpenApk(const QString &p)
{
    (new PreOpenApk(p, this))->exec();
}

void Ide::onOpenDir(const QString &p)
{
    _project = p;
    emit projectOpen(p);
    QString manifest;
    if (QFile::exists(manifest = PathUtils::combine(p, "AndroidManifest.xml")))
    {
        emit fileOpen(manifest);
    }
}

void Ide::onRunnableStarted()
{
    onRunnableStopped();
    _pleaseWait = new PleaseWait(this);
    _pleaseWait->show();
}

void Ide::onRunnableStopped()
{
    if (_pleaseWait)
    {
        _pleaseWait->finish();
    }
}

void Ide::onSignFailure(const QString &a)
{
    _statusBar->showMessage(__("sign_failure", "messages", a));
}

void Ide::onSignSuccess(const QString &a)
{
    _signed = true;
    _statusBar->showMessage(__("sign_success", "messages", a));
    QMessageBox mb;
    mb.addButton(__("install", "buttons"), QMessageBox::AcceptRole);
    mb.addButton(QMessageBox::Close);
    mb.setText(__("apk_signed", "messages"));
    mb.setWindowTitle(__("apk_signed", "titles"));
    if (mb.exec() != QMessageBox::Close)
    {
        Ide::onMenuBarProjectInstall();
    }
}

Ide::~Ide()
{
    Preferences::get()
            ->setSessionProject(_project)
            ->save();
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
