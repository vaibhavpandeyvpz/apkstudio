#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QFileIconProvider>
#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QMap>
#include <QProgressDialog>
#include <QStackedWidget>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QToolBar>
#include <QTreeWidget>
#include <QVBoxLayout>
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
    explicit MainWindow(const QMap<QString, QString> &versions, QWidget *parent = nullptr);
    ~MainWindow();
    void openApkFile(const QString &apkPath);
    void openFile(const QString &file);
    QWidget* findTabWidget(const QString& path);
protected:
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event) override;
private:
    QAction *m_ActionBuild1;
    QAction *m_ActionBuild2;
    QAction *m_ActionClose;
    QAction *m_ActionCloseAll;
    QAction *m_ActionCopy;
    QAction *m_ActionCut;
    QAction *m_ActionFind;
    QAction *m_ActionFindInFiles;
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
    QAction *m_ActionViewProject;
    QAction *m_ActionViewFiles;
    QAction *m_ActionViewConsole;
    QAction *m_ActionViewToolBar;
    QStackedWidget *m_CentralStack;
    QDockWidget *m_DockProject;
    QDockWidget *m_DockFiles;
    QDockWidget *m_DockConsole;
    QTextEdit *m_EditConsole;
    QList<QMetaObject::Connection> m_EditorConnections;
    QFileIconProvider m_FileIconProvider;
    FindReplaceDialog *m_FindReplaceDialog;
    class FindInFilesDialog *m_FindInFilesDialog;
    QLineEdit *m_SearchFiles;
    QLineEdit *m_SearchProjects;
    QListView *m_ListOpenFiles;
    QToolBar *m_MainToolBar;
    QStandardItemModel *m_ModelOpenFiles;
    QSortFilterProxyModel *m_FilesProxyModel;
    QProgressDialog *m_ProgressDialog;
    QTreeWidget *m_ProjectsTree;
    QLabel *m_StatusCursor;
    QLabel *m_StatusMessage;
    QTabWidget *m_TabEditors;
    QWidget *buildCentralWidget();
    QDockWidget *buildConsoleDock();
    QDockWidget *buildFilesDock();
    QToolBar *buildMainToolBar();
    QMenuBar *buildMenuBar();
    QDockWidget *buildProjectsDock();
    QStatusBar *buildStatusBar(const QMap<QString, QString> &versions);
    int findTabIndex(const QString& path);
    QStringList getProjectRoots();
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
    void handleActionFindInFiles();
    void handleActionFolder();
    void handleActionGoto();
    void handleActionInstall();
    void handleActionInstallFramework();
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
    void handleFilesSearchChanged(const QString &text);
    void handleProjectsSearchChanged(const QString &text);
    void handleTreeContextMenu(const QPoint &point);
    void handleTreeDoubleClicked(const QModelIndex &index);
    void handleTreeSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void openFindReplaceDialog(QPlainTextEdit *edit, const bool replace);
    void openProject(const QString &folder, const bool last = false);
    void reloadChildren(QTreeWidgetItem *item);
    void filterProjectTreeItems(QTreeWidgetItem *item, const QString &filter);
    void updateWindowTitle();
#ifdef Q_OS_LINUX
    void checkAndInstallDesktopFile();
#endif
private:
    bool saveTab(int index);
};

Q_DECLARE_METATYPE(MainWindow::TreeItemType);

#endif // MAINWINDOW_H
