#ifndef IDE_H
#define IDE_H

#include <QMainWindow>
#include <QPointer>
#include <QProgressDialog>
#include "macros.h"

AS_NAMESPACE_START

class StatusBar;

class Ide : public QMainWindow
{
    Q_OBJECT
private:
    AS_CONNECTIONS_LIST
    QString _apk;
    QPointer<QProgressDialog> _progressDialog;
    QString _project;
    StatusBar *_statusBar;
protected:
    void closeEvent(QCloseEvent *e);
public:
    explicit Ide(QWidget *parent = 0);
    ~Ide();
public slots:
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
    void onMenuBarProjectOpen(const QString &project);
    void onMenuBarProjectReload();
    void onMenuBarProjectSignExport();
    void onRunnableStarted();
    void onRunnableStopped();
    void onSignFailure(const QString &apk);
    void onSignSuccess(const QString &apk);
signals:
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

AS_NAMESPACE_END

#endif // IDE_H
