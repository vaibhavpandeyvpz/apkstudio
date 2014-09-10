#ifndef MENUBARUI_H
#define MENUBARUI_H

#include <QMenuBar>

#include "settings.h"
#include "utility.h"

class MenuBarUI : public QMenuBar
{
    Q_OBJECT
protected:
    // Menus
    QMenu *_adb;
    QMenu *_build;
    QMenu *_edit;
    QMenu *_feedback;
    QMenu *_file;
    QMenu *_help;
    QMenu *_open;
    QMenu *_project;
    QMenu *_recent_files;
    QMenu *_recent_projects;
    QMenu *_scripts;
    QMenu *_tools;
    QMenu *_views;
    QMenu *_window;
    // Actions
    QAction *_about;
    QAction *_adb_kill;
    QAction *_adb_reset;
    QAction *_adb_start;
    QAction *_applications_manager;
    QAction *_build_;
    QAction *_build_all;
    QAction *_clean;
    QAction *_clean_all;
    QAction *_close_file;
    QAction *_close_project;
    QAction *_contribute;
    QAction *_copy;
    QAction *_cut;
    QAction *_device_manager;
    QAction *_donate;
    QAction *_export;
    QAction *_feedback_issues;
    QAction *_feedback_thanks;
    QAction *_file_manager;
    QAction *_find;
    QAction *_full_screen;
    QAction *_goto;
    QAction *_logcat;
    QAction *_open_apk;
    QAction *_open_file;
    QAction *_open_project;
    QAction *_paste;
    QAction *_print;
    QAction *_properties;
    QAction *_quit;
    QAction *_redo;
    QAction *_replace;
    QAction *_restart;
    QAction *_save;
    QAction *_save_all;
    QAction *_shell;
    QAction *_sidebar;
    QAction *_sign;
    QAction *_split;
    QAction *_undo;
    QAction *_views_files;
    QAction *_views_logs;
    QAction *_views_outline;
    QAction *_views_projects;
    QAction *_views_tasks;
    QAction *_windowed;
    QAction *_zipalign;
protected:
    static QString translate(const char *key) {
        return Utility::translate("menubar", key);
    }
private:
    void prepare();
protected Q_SLOTS:
    virtual void onRestart() = 0;
    virtual void onQuit() = 0;
public:
    explicit MenuBarUI(QWidget *parent = 0)
        : QMenuBar(parent) {
        prepare();
    }
    ~MenuBarUI() {
    }
};

#endif // MENUBARUI_H
