#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileIconProvider>
#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QProgressDialog>
#include <QStackedWidget>
#include <QTextEdit>
#include <QTreeWidget>
#include "processutils.h"

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
    QTextEdit *m_EditConsole;
    QList<QMetaObject::Connection> m_EditorConnections;
    QMap<QString, int> m_MapOpenFiles;
    QFileIconProvider m_FileIconProvider;
    QProgressDialog *m_ProgressDialog;
    QTreeWidget *m_ProjectsTree;
    QLabel *m_StatusMessage;
    QTabWidget *m_TabEditors;
    QLabel *m_VersionAdb;
    QLabel *m_VersionApktool;
    QLabel *m_VersionJadx;
    QLabel *m_VersionJava;
    QLabel *m_VersionUberApkSigner;
    QWidget *buildCentralWidget();
    QDockWidget *buildConsoleDock();
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
    void handleActionSign();
    void handleActionUndo();
    void handleClipboardDataChanged();
    void handleCommandFinished(const ProcessResult &result);
    void handleCommandStarting(const QString &exe, const QStringList &args);
    void handleDecompileFailed(const QString &apk);
    void handleDecompileFinished(const QString &apk, const QString &folder);
    void handleDecompileProgress(const int percent, const QString &message);
    void handleInstallFailed(const QString &apk);
    void handleInstallFinished(const QString &apk);
    void handleRecompileFailed(const QString &folder);
    void handleRecompileFinished(const QString &folder);
    void handleSignFailed(const QString &apk);
    void handleSignFinished(const QString &apk);
    void handleTabChanged(const int index);
    void handleTabCloseRequested(const int index);
    void handleTreeContextMenu(const QPoint &point);
    void handleTreeDoubleClicked(const QModelIndex &index);
    void handleTreeSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void handleVersionResolved(const QString &binary, const QString &version);
    void openFile(const QString &file);
    void openProject(const QString &folder);
    void reloadChildren(QTreeWidgetItem *item);
};

Q_DECLARE_METATYPE(MainWindow::TreeItemType);

#endif // MAINWINDOW_H
