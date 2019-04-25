#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileIconProvider>
#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QMap>
#include <QProgressDialog>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QTreeWidget>
#include "findreplacedialog.h"
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
    QFileIconProvider m_FileIconProvider;
    FindReplaceDialog *m_FindReplaceDialog;
    QListView *m_ListOpenFiles;
    QStandardItemModel *m_ModelOpenFiles;
    QProgressDialog *m_ProgressDialog;
    QTreeWidget *m_ProjectsTree;
    QLabel *m_StatusCursor;
    QLabel *m_StatusMessage;
    QTabWidget *m_TabEditors;
    QLabel *m_VersionAdb;
    QLabel *m_VersionApktool;
    QLabel *m_VersionJadx;
    QLabel *m_VersionJava;
    QLabel *m_VersionUberApkSigner;
    QWidget *buildCentralWidget();
    QDockWidget *buildConsoleDock();
    QDockWidget *buildFilesDock();
    QToolBar *buildMainToolBar();
    QMenuBar *buildMenuBar();
    QDockWidget *buildProjectsDock();
    QStatusBar *buildStatusBar();
    int findTabIndex(const QString& path);
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
    void handleCursorPositionChanged();
    void handleDecompileFailed(const QString &apk);
    void handleDecompileFinished(const QString &apk, const QString &folder);
    void handleDecompileProgress(const int percent, const QString &message);
    void handleFilesSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
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
    void openFindReplaceDialog(QPlainTextEdit *edit, const bool replace);
    void openProject(const QString &folder, const bool last = false);
    void reloadChildren(QTreeWidgetItem *item);
private:
    bool saveTab(int index);
};

Q_DECLARE_METATYPE(MainWindow::TreeItemType);

#endif // MAINWINDOW_H
