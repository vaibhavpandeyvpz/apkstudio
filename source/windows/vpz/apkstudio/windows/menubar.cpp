#include "menubar.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

MenuBar::MenuBar(QWidget *parent) :
    QMenuBar(parent)
{
    // Initialize parent menus
    QMenu *build = new QMenu(translate("menu_build"), this);
    QMenu *edit = new QMenu(translate("menu_edit"), this);
    QMenu *file = new QMenu(translate("menu_file"), this);
    QMenu *help = new QMenu(translate("menu_help"), this);
    QMenu *project = new QMenu(translate("menu_project"), this);
    QMenu *scripts = new Components::Scripts(this);
    QMenu *window = new QMenu(translate("menu_window"), this);
    QMenu *tools = new QMenu(translate("menu_tools"), this);
    // Initialize toggle groups
    QActionGroup *toggles = new QActionGroup(this);
    // Initialize sub-menus
    QMenu *adb = new QMenu(translate("item_adb"), tools);
    QMenu *feedback = new QMenu(translate("item_feedback"), help);
    QMenu *open = new QMenu(translate("item_open"), file);
    QMenu *recents = new Components::Recents(file);
    QMenu *views = new QMenu(translate("item_views"), window);
    // Add build items
    APKS_MENUITEM(toggles, false, build, clean, Clean, 0);
    APKS_MENUITEM(toggles, false, build, clean_all, CleanAll, 0);
    build->addSeparator();
    APKS_MENUITEM(toggles, false, build, build, Build, QKeySequence(Qt::Key_F5));
    APKS_MENUITEM(toggles, false, build, build_all, BuildAll, 0);
    build->addSeparator();
    APKS_MENUITEM(toggles, false, build, sign, Sign, 0);
    APKS_MENUITEM(toggles, false, build, zipalign, ZipAlign, 0);
    // Add edit items
    APKS_MENUITEM(toggles, false, edit, undo, Undo, QKeySequence::Undo);
    APKS_MENUITEM(toggles, false, edit, redo, Redo, QKeySequence::Redo);
    edit->addSeparator();
    APKS_MENUITEM(toggles, false, edit, cut, Cut, QKeySequence::Cut);
    APKS_MENUITEM(toggles, false, edit, copy, Copy, QKeySequence::Copy);
    APKS_MENUITEM(toggles, false, edit, paste, Paste, QKeySequence::Paste);
    edit->addSeparator();
    APKS_MENUITEM(toggles, false, edit, find, Find, QKeySequence::Find);
    APKS_MENUITEM(toggles, false, edit, replace, Replace, QKeySequence::Replace);
    APKS_MENUITEM(toggles, false, edit, goto, Goto, 0);
    edit->addSeparator();
    // Add file items
    APKS_MENUITEM(toggles, false, open, open_apk, OpenApk, QKeySequence::Open);
    APKS_MENUITEM(toggles, false, open, open_project, OpenProject, 0);
    open->addSeparator();
    APKS_MENUITEM(toggles, false, open, open_file, OpenFile, 0);
    file->addAction(open->menuAction());
    APKS_MENUITEM(toggles, false, file, close_file, CloseFile, QKeySequence::Close);
    APKS_MENUITEM(toggles, false, file, close_project, CloseProject, 0);
    file->addSeparator();
    APKS_MENUITEM(toggles, false, file, save, Save, QKeySequence::Save);
    APKS_MENUITEM(toggles, false, file, save_all, SaveAll, QKeySequence::SaveAs);
    file->addSeparator();
    APKS_MENUITEM(toggles, false, file, print, Print, QKeySequence::Print);
    file->addSeparator();
    APKS_MENUITEM(toggles, false, file, restart, Restart, 0);
    file->addSeparator();
    file->addAction(recents->menuAction());
    file->addSeparator();
    APKS_MENUITEM(toggles, false, file, quit, Quit, QKeySequence::Quit);
    // Add help items
    APKS_MENUITEM(toggles, false, feedback, feedback_thanks, FeedbackThanks, 0);
    APKS_MENUITEM(toggles, false, feedback, feedback_issues, FeedbackIssues, 0);
    APKS_MENUITEM(toggles, false, help, about, About, QKeySequence::HelpContents);
    help->addSeparator();
    APKS_MENUITEM(toggles, false, help, contribute, Contribute, 0);
    APKS_MENUITEM(toggles, false, help, donate, Donate, 0);
    help->addAction(feedback->menuAction());
    // Add project items
    APKS_MENUITEM(toggles, false, project, export, Export, QKeySequence(Qt::CTRL + Qt::Key_E));
    project->addSeparator();
    APKS_MENUITEM(toggles, false, project, properties, Properties, 0);
    // Add tools items
    APKS_MENUITEM(toggles, false, adb, adb_kill, AdbKill, 0);
    APKS_MENUITEM(toggles, false, adb, adb_reset, AdbReset, 0);
    APKS_MENUITEM(toggles, false, adb, adb_start, AdbReset, 0);
    tools->addAction(adb->menuAction());
    tools->addSeparator();
    APKS_MENUITEM(toggles, false, tools, device_manager, DeviceManager, 0);
    tools->addSeparator();
    APKS_MENUITEM(toggles, false, tools, shell, Shell, 0);
    APKS_MENUITEM(toggles, false, tools, logcat, Logcat, 0);
    tools->addSeparator();
    APKS_MENUITEM(toggles, false, tools, file_manager, FileManager, 0);
    APKS_MENUITEM(toggles, false, tools, applications_manager, ApplicationsManager, 0);
    // Add window items
    APKS_MENUITEM(toggles, true, views, views_files, ViewFiles, 0);
    APKS_MENUITEM(toggles, true, views, views_logs, ViewLogs, 0);
    APKS_MENUITEM(toggles, true, views, views_outline, ViewOutline, 0);
    APKS_MENUITEM(toggles, true, views, views_projects, ViewProjects, 0);
    APKS_MENUITEM(toggles, true, views, views_tasks, ViewTasks, 0);
    APKS_MENUITEM(toggles, false, window, full_screen, FullScreen, QKeySequence::FullScreen);
    window->addSeparator();
    APKS_MENUITEM(toggles, true, window, sidebar, Sidebar, 0);
    window->addAction(views->menuAction());
    window->addSeparator();
    APKS_MENUITEM(toggles, false, window, split, Split, 0);
    // Add menus
    addAction(file->menuAction());
    addAction(edit->menuAction());
    addAction(build->menuAction());
    addAction(project->menuAction());
    addAction(tools->menuAction());
    addAction(scripts->menuAction());
    addAction(window->menuAction());
    addAction(help->menuAction());
    // Attach toggles
    connect(toggles, SIGNAL(triggered(QAction *)), parent, SLOT(onActionToggle(QAction *)));
    toggles->setExclusive(false);
    // Invalidate
    recents->setEnabled(false);
    scripts->setEnabled(false);
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ
