#ifndef IDE_H
#define IDE_H

#include <QDropEvent>
#include <QMainWindow>
#include <QPointer>
#include "include/consoledock.h"
#include "include/projectdock.h"
#include "macros.h"

APP_NAMESPACE_START

class PleaseWait;

class StatusBar;

class Ide : public QMainWindow
{
    Q_OBJECT
private:
    APP_CONNECTIONS_LIST
    QString _apk;
    bool _signed;
    QPointer<PleaseWait> _pleaseWait;
    QString _project;
    bool _quit;
    StatusBar *_statusBar;
protected:
    void closeEvent(QCloseEvent *event);
    void dropEvent(QDropEvent* event);
    inline void dragEnterEvent(QDragEnterEvent *event) { event->acceptProposedAction(); }
    inline void dragLeaveEvent(QDragLeaveEvent *event) { event->accept(); }
    inline void dragMoveEvent(QDragMoveEvent *event) { event->acceptProposedAction(); }
public:
    explicit Ide(QWidget *parent = 0);
    ~Ide();
public Q_SLOTS:
    void onBuildFailure(const QString &project);
    void onBuildSuccess(const QString &apk);
    void onDecodeFailure(const QString &apk);
    void onDecodeSuccess(const QString &project);
    void onFileChanged(const QString &path);
    void onFileOpen(const QString &path);
    void onFileSaved(const QString &path);
    void onInit();
    void onInstallFailure(const QString &apk);
    void onInstallSuccess(const QString &apk);
    inline void onMenuBarEditCopy() { emit editCopy(); }
    inline void onMenuBarEditCut() { emit editCut(); }
    inline void onMenuBarEditFind() { emit editFind(); }
    inline void onMenuBarEditGoto() { emit editGoto(); }
    inline void onMenuBarEditPaste() { emit editPaste(); }
    inline void onMenuBarEditRedo() { emit editRedo(); }
    inline void onMenuBarEditReplace() { emit editReplace(); }
    void onMenuBarEditSettings();
    inline void onMenuBarEditUndo() { emit editUndo(); }
    inline void onMenuBarFileClose() { emit fileClose(); }
    inline void onMenuBarFileCloseAll() { emit fileCloseAll(); }
    void onMenuBarFileOpenApk();
    void onMenuBarFileOpenDir();
    void onMenuBarFileOpenFile();
    inline void onMenuBarFileQuit() { close(); }
    inline void onMenuBarFileSave() { emit fileSave(); }
    inline void onMenuBarFileSaveAll() { emit fileSaveAll(); }
    void onMenuBarFileTerminal();
    void onMenuBarHelpAbout();
    void onMenuBarHelpContribute();
    void onMenuBarHelpDocumentation();
    void onMenuBarHelpFeedbackIssues();
    void onMenuBarHelpFeedbackThanks();
    void onMenuBarProjectBuild();
    void onMenuBarProjectInstall();
    void onMenuBarProjectReload();
    void onMenuBarProjectSignExport();
    void onToolBarProjectSign();
    void onMenuBarProjectBrowseFiles();
    void onOpenApk(const QString &apk);
    void onOpenDir(const QString &project);
    void onRunnableStarted();
    void onRunnableStopped();
    void onSignFailure(const QString &apk);
    void onSignSuccess(const QString &apk);
Q_SIGNALS:
    void editCopy();
    void editCut();
    void editFind();
    void editGoto();
    void editPaste();
    void editRedo();
    void editReplace();
    void editUndo();
    void fileClose();
    void fileCloseAll();
    void fileOpen(const QString &path);
    void fileSave();
    void fileSaveAll();
    void projectOpen(const QString &path);
    void projectReload();
};

APP_NAMESPACE_END

#endif // IDE_H
