#include <QCloseEvent>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <QMimeData>
#include <QProcess>
#include <QProgressBar>
#include <QTimer>
#include "adbdock.h"
#include "buildrunnable.h"
#include "constants.h"
#include "editortabs.h"
#include "coderhighlighterdefinition.h"
#include "coderhighlightertheme.h"
#include "decoderunnable.h"
#include "ide.h"
#include "fileutils.h"
#include "installrunnable.h"
#include "jarsignerdock.h"
#include "javadock.h"
#include "menubar.h"
#include "pathutils.h"
#include "preferences.h"
#include "preopenapk.h"
#include "process.h"
#include "projectdock.h"
#include "qrc.h"
#include "runner.h"
#include "settingseditor.h"
#include "signexportapk.h"
#include "signrunnable.h"
#include "statusbar.h"
#include "textutils.h"
#include "toolbar.h"
#include "zipaligndock.h"

AS_NAMESPACE_START

Ide::Ide(QWidget *parent)
    : QMainWindow(parent), _progressDialog(nullptr)
{
    addToolBar(Qt::TopToolBarArea, new ToolBar(this));
    setAcceptDrops(true);
    setCentralWidget(new EditorTabs(this));
    setDockOptions(AllowTabbedDocks | AnimatedDocks);
    setMenuBar(new MenuBar(this));
    setMinimumSize(800, 600);
    setStatusBar(_statusBar = new StatusBar(this));
    setWindowTitle(Qrc::text("ide.title"));
}

void Ide::closeEvent(QCloseEvent *e)
{
    QMessageBox mb(QMessageBox::Question, Qrc::text("dialog.quit.title"), Qrc::text("dialog.quit.message"));
    mb.addButton(QMessageBox::Yes);
    mb.addButton(QMessageBox::No);
    mb.setWindowIcon(Qrc::icon("dialog_quit"));
    if (QMessageBox::Yes == mb.exec())
    {
        auto p = Preferences::get();
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
    _statusBar->showMessage(Qrc::text("statusbar.message.build_failure").arg(p));
}

void Ide::onBuildSuccess(const QString &a)
{
    _apk = a;
    _statusBar->showMessage(Qrc::text("statusbar.message.build_success").arg(a));
}

void Ide::onDecodeFailure(const QString &a)
{
    _statusBar->showMessage(Qrc::text("statusbar.message.decode_failure").arg(a));
}

void Ide::onDecodeSuccess(const QString &p)
{
    _statusBar->showMessage(Qrc::text("statusbar.message.decode_success").arg(p));
    onOpenDir(p);
}

void Ide::onFileChanged(const QString &p)
{
    if (p.isEmpty())
    {
        setWindowTitle(Qrc::text("ide.title"));
    }
    else
    {
        QFileInfo fi(p);
        setWindowTitle(Qrc::text("ide.title.alt").arg(fi.fileName()));
    }
}

void Ide::onFileOpen(const QString &p)
{
    emit fileOpen(p);
}

void Ide::onFileSaved(const QString &p)
{
    _statusBar->showMessage(Qrc::text("statusbar.message.file_saved").arg(p));
}

void Ide::onInit()
{
    auto p = Preferences::get();
    if (p->wasWindowMaximized())
    {
        showMaximized();
    }
    else
    {
        resize(p->windowSize());
    }
    addDockWidget(Qt::LeftDockWidgetArea, new ProjectDock(this));
    auto java = new JavaDock(this);
    addDockWidget(Qt::BottomDockWidgetArea, java);
    auto zipAlign = new ZipAlignDock(this);
    addDockWidget(Qt::BottomDockWidgetArea, zipAlign);
    tabifyDockWidget(java, zipAlign);
    auto jarSigner = new JarSignerDock(this);
    addDockWidget(Qt::BottomDockWidgetArea, jarSigner);
    tabifyDockWidget(zipAlign, jarSigner);
    auto adb = new AdbDock(this);
    addDockWidget(Qt::BottomDockWidgetArea, adb);
    tabifyDockWidget(jarSigner, adb);
    restoreState(p->docksState());
}

void Ide::onInstallFailure(const QString &a)
{
    _statusBar->showMessage(Qrc::text("statusbar.message.install_failure").arg(a));
}

void Ide::onInstallSuccess(const QString &a)
{
    _statusBar->showMessage(Qrc::text("statusbar.message.install_success").arg(a));
}

void Ide::onMenuBarEditSettings()
{
    (new SettingsEditor(this))->exec();
}

void Ide::onMenuBarFileOpenApk()
{
    QFileDialog d(this, Qrc::text("dialog.open.apk.title"), Preferences::get()->previousDir(), Qrc::text("dialog.open.apk.filter"));
    d.setAcceptMode(QFileDialog::AcceptOpen);
    d.setFileMode(QFileDialog::ExistingFile);
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
    QFileDialog d(this, Qrc::text("dialog.open.dir.title"), Preferences::get()->previousDir(), Qrc::text("dialog.open.dir.filter"));
    d.setAcceptMode(QFileDialog::AcceptOpen);
    d.setFileMode(QFileDialog::ExistingFile);
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

void Ide::onMenuBarFileOpenDirProxy(const QString &p)
{
    onOpenDir(p);
}

void Ide::onMenuBarFileOpenFile()
{
    QFileDialog d(this, Qrc::text("dialog.open.file.title"), Preferences::get()->previousDir(), Qrc::text("dialog.open.file.filter"));
    d.setAcceptMode(QFileDialog::AcceptOpen);
    d.setFileMode(QFileDialog::ExistingFiles);
    if (d.exec() == QFileDialog::Accepted)
    {
        QStringList files;
        if ((files = d.selectedFiles()).isEmpty() == false)
        {
            Preferences::get()->setPreviousDir(d.directory().absolutePath())->save();
            for (const QString &f : files)
            {
                emit fileOpen(f);
            }
        }
    }
}

void Ide::onMenuBarFileTerminal()
{
#ifdef Q_OS_WIN
    QString c("cmd.exe");
    QStringList a("/k");
    a << QString("cd /d %1").arg(Preferences::get()->binariesPath());
#else
    QString c("gnome-terminal");
    QStringList a(QString("--working-directory=%1").arg(Preferences::get()->binariesPath()));
#endif
    QProcess::startDetached(c, a);
}

void Ide::onMenuBarHelpAbout()
{
    QMessageBox box;
    box.setIconPixmap(Qrc::image("logo"));
    box.setInformativeText(FileUtils::read(QString(QRC_HTML).arg("about")));
    box.setText(Qrc::text("dialog.about.version").arg(APP_VERSION));
    box.setWindowIcon(Qrc::icon("dialog_about"));
    box.setWindowTitle(Qrc::text("dialog.about.title"));
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
    if (_project.isNull() || _project.isEmpty())
    {
        QMessageBox::warning(this, Qrc::text("dialog.warning.no_project.title"), Qrc::text("dialog.warning.no_project.message"), QMessageBox::Close);
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
        QMessageBox::warning(this, Qrc::text("dialog.warning.no_apk.title"), Qrc::text("dialog.warning.no_apk.message"), QMessageBox::Close);
    }
    else
    {
        Runner::get()->add(new InstallRunnable(_apk, this));
    }
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

void Ide::onOpenApk(const QString &p)
{
    PreOpenApk *d = new PreOpenApk(p, this);
    if (d->exec() == QDialog::Accepted)
    {
        Runner::get()->add(new DecodeRunnable(d->apk(), d->project(), d->framework(), this));
    }
    delete d;
}

void Ide::onMenuBarProjectReload()
{
    emit projectReload();
}

void Ide::onMenuBarProjectSignExport()
{

    if (_apk.isNull() || _apk.isEmpty())
    {
        QMessageBox::warning(this, Qrc::text("dialog.warning.no_apk.title"), Qrc::text("dialog.warning.no_apk.message"), QMessageBox::Close);
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

void Ide::onRunnableStarted()
{
    onRunnableStopped();
    QProgressBar *bar;
    _progressDialog = new QProgressDialog(this, Qt::CustomizeWindowHint);
    _progressDialog->setBar(bar = new QProgressBar(_progressDialog));
    _progressDialog->setCancelButton(nullptr);
    _progressDialog->setLabelText(Qrc::text("dialog.waiting.message"));
    _progressDialog->setRange(0, 0);
    _progressDialog->setWindowModality(Qt::WindowModal);
    _progressDialog->show();
    bar->setTextVisible(false);
}

void Ide::onRunnableStopped()
{
    if (_progressDialog)
    {
        _progressDialog->close();
        delete _progressDialog;
    }
}

void Ide::onSignFailure(const QString &a)
{
    _statusBar->showMessage(Qrc::text("statusbar.message.sign_failure").arg(a));
}

void Ide::onSignSuccess(const QString &a)
{
    QMessageBox mb;
    mb.addButton(Qrc::text("dialog.sign.success.open_folder"), QMessageBox::AcceptRole);
    mb.addButton(QMessageBox::Close);
    mb.setText(Qrc::text("dialog.sign.success.message"));
    mb.setWindowTitle(Qrc::text("dialog.sign.success.title"));
    if (mb.exec() != QMessageBox::Close)
    {
        FileUtils::show(a);
    }
    _statusBar->showMessage(Qrc::text("statusbar.message.sign_success").arg(a));
}

Ide::~Ide()
{
    AS_CONNECTIONS_DISCONNECT
}

AS_NAMESPACE_END
