#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private:
    QMenuBar* buildMenuBar();
private slots:
    void handleActionAbout();
    void handleActionApk();
    void handleActionBuild();
    void handleActionClose();
    void handleActionCloseAll();
    void handleActionContribute();
    void handleActionCopy();
    void handleActionCut();
    void handleActionDirectory();
    void handleActionDocumentation();
    void handleActionFile();
    void handleActionFind();
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
};

#endif // MAINWINDOW_H
