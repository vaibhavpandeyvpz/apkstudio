#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileIconProvider>
#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QProgressDialog>
#include <QStackedWidget>
#include <QTreeWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum TreeItemType {
        Project = 0,
        Folder,
        File
    };
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private:
    QAction *m_ActionBuild1;
    QAction *m_ActionBuild2;
    QAction *m_ActionClose;
    QAction *m_ActionCloseAll;
    QAction *m_ActionCopy;
    QAction *m_ActionCut;
    QAction *m_ActionFind;
    QAction *m_ActionGoto;
    QAction *m_ActionInstall1;
    QAction *m_ActionInstall2;
    QAction *m_ActionPaste;
    QAction *m_ActionRedo;
    QAction *m_ActionReplace;
    QAction *m_ActionSave;
    QAction *m_ActionSaveAll;
    QAction *m_ActionSign;
    QAction *m_ActionUndo;
    QStackedWidget *m_CentralStack;
    QFileIconProvider m_FileIconProvider;
    QProgressDialog *m_ProgressDialog;
    QTreeWidget *m_ProjectsTree;
    QLabel *m_StatusMessage;
    QLabel *m_VersionAdb;
    QLabel *m_VersionApktool;
    QLabel *m_VersionJadx;
    QLabel *m_VersionJava;
    QLabel *m_VersionUberApkSigner;
    QWidget *buildCentralWidget();
    QToolBar *buildMainToolBar();
    QMenuBar *buildMenuBar();
    QDockWidget *buildProjectsDock();
    QStatusBar *buildStatusBar();
private slots:
    void handleActionAbout();
    void handleActionApk();
    void handleActionBuild();
    void handleActionClose();
    void handleActionCloseAll();
    void handleActionContribute();
    void handleActionCopy();
    void handleActionCut();
    void handleActionDocumentation();
    void handleActionFile();
    void handleActionFind();
    void handleActionFolder();
    void handleActionGoto();
    void handleActionInstall();
    void handleActionPaste();
    void handleActionQuit();
    void handleActionRedo();
    void handleActionReplace();
    void handleActionReportIssues();
    void handleActionSave();
    void handleActionSaveAll();
    void handleActionSayThanks();
    void handleActionSettings();
    void handleActionSignExport();
    void handleActionUndo();
    void handleDecompileFailed(const QString &apk);
    void handleDecompileFinished(const QString &apk, const QString &folder);
    void handleDecompileProgress(const int percent, const QString &message);
    void handleTreeDoubleClicked(const QModelIndex &index);
    void handleVersionResolved(const QString &binary, const QString &version);
    void reloadChildren(QTreeWidgetItem *item);
};

Q_DECLARE_METATYPE(MainWindow::TreeItemType);

#endif // MAINWINDOW_H
