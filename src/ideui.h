#ifndef IDEUI_H
#define IDEUI_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QStatusBar>

#include "editorspanel.h"
#include "filespanel.h"
#include "logspanel.h"
#include "menubar.h"
#include "outlinepanel.h"
#include "projectspanel.h"
#include "settings.h"
#include "taskspanel.h"
#include "toolbar.h"
#include "utility.h"

class IDEUI : public QMainWindow
{
    Q_OBJECT
protected:
    int _exit_code;
    EditorsPanel *_editors_panel;
    FilesPanel *_files_panel;
    LogsPanel *_logs_panel;
    MenuBar *_menubar;
    OutlinePanel *_outline_panel;
    ProjectsPanel *_projects_panel;
    QStatusBar *_statusbar;
    TasksPanel *_tasks_panel;
    ToolBar *_toolbar;
protected:
    static QString translate(const char *key) {
        return Utility::translate("ide", key);
    }
private:
    void closeEvent(QCloseEvent *event);
    void prepare();
public:
    explicit IDEUI(QWidget *parent = 0)
        : QMainWindow(parent) {
        prepare();
    }
    ~IDEUI() {
    }
public Q_SLOTS:
    void inflate();
};

#endif // IDEUI_H
