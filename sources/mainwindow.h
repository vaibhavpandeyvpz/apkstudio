#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QProgressDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private:
    QProgressDialog *m_ProgressDialog;
    QLabel *m_StatusMessage;
    QLabel *m_VersionAdb;
    QLabel *m_VersionApktool;
    QLabel *m_VersionJadx;
    QLabel *m_VersionJava;
    QLabel *m_VersionUberApkSigner;
    QToolBar *buildMainToolBar();
    QMenuBar *buildMenuBar();
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
    void handleVersionResolved(const QString &binary, const QString &version);
};

#endif // MAINWINDOW_H
