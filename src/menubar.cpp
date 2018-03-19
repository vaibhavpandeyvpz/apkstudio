#include <QDir>
#include "include/menubar.h"
#include "include/preferences.h"
#include "include/qrc.h"
#include "include/runner.h"

APP_NAMESPACE_START

MenuBar::MenuBar(QWidget *p)
    : QMenuBar(p)
{
    addFileMenu();
    addEditMenu();
    addProjectMenu();
    addHelpMenu();
}

void MenuBar::addEditMenu()
{
    QMenu *m = new QMenu(__("edit", "menubar"), this);
    m->addAction(__("undo", "menubar"), parent(), SLOT(onMenuBarEditUndo()), QKeySequence::Undo);
    m->addAction(__("redo", "menubar"), parent(), SLOT(onMenuBarEditRedo()), QKeySequence::Redo);
    m->addSeparator();
    m->addAction(__("cut", "menubar"), parent(), SLOT(onMenuBarEditCut()), QKeySequence::Cut);
    m->addAction(__("copy", "menubar"), parent(), SLOT(onMenuBarEditCopy()), QKeySequence::Copy);
    m->addAction(__("paste", "menubar"), parent(), SLOT(onMenuBarEditPaste()), QKeySequence::Paste);
    m->addSeparator();
    m->addAction(__("find", "menubar"), parent(), SLOT(onMenuBarEditFind()), QKeySequence::Find);
    m->addAction(__("replace", "menubar"), parent(), SLOT(onMenuBarEditReplace()), QKeySequence::Replace);
    m->addAction(__("goto", "menubar"), parent(), SLOT(onMenuBarEditGoto()));
    m->addSeparator();
    m->addAction(__("settings", "menubar"), parent(), SLOT(onMenuBarEditSettings()), QKeySequence::Preferences);
    addAction(m->menuAction());
}

void MenuBar::addFileMenu()
{
    QMenu *m = new QMenu(__("file", "menubar"), this);
    QMenu *o = new QMenu(__("open", "menubar"), m);
    o->addAction(__("apk", "menubar"), parent(), SLOT(onMenuBarFileOpenApk()), QKeySequence::New);
    o->addAction(__("directory", "menubar"), parent(), SLOT(onMenuBarFileOpenDir()), QKeySequence::Open);
    o->addSeparator();
    o->addAction(__("file", "menubar"), parent(), SLOT(onMenuBarFileOpenFile()));
    m->addAction(o->menuAction());
    m->addSeparator();
    m->addAction(__("close", "menubar"), parent(), SLOT(onMenuBarFileClose()), QKeySequence::Close);
    m->addAction(__("close_all", "menubar"), parent(), SLOT(onMenuBarFileCloseAll()));
    m->addSeparator();
    m->addAction(__("save", "menubar"), parent(), SLOT(onMenuBarFileSave()), QKeySequence::Save);
    m->addAction(__("save_all", "menubar"), parent(), SLOT(onMenuBarFileSaveAll()));
    m->addSeparator();
    m->addAction(__("terminal", "menubar"), parent(), SLOT(onMenuBarFileTerminal()));
    m->addSeparator();
    m->addAction(__("quit", "menubar"), parent(), SLOT(onMenuBarFileQuit()), QKeySequence::Quit);
    addAction(m->menuAction());
}

void MenuBar::addHelpMenu()
{
    QMenu *m = new QMenu(__("help", "menubar"), this);
    m->addAction(__("about", "menubar"), parent(), SLOT(onMenuBarHelpAbout()));
    m->addAction(__("documentation", "menubar"), parent(), SLOT(onMenuBarHelpDocumentation()));
    m->addSeparator();
    QMenu *f = new QMenu(__("feedback", "menubar"), m);
    f->addAction(__("say_thanks", "menubar"), parent(), SLOT(onMenuBarHelpFeedbackThanks()));
    f->addAction(__("report_issues", "menubar"), parent(), SLOT(onMenuBarHelpFeedbackIssues()));
    m->addAction(f->menuAction());
    m->addAction(__("contribute", "menubar"), parent(), SLOT(onMenuBarHelpContribute()));
    addAction(m->menuAction());
}

void MenuBar::addProjectMenu()
{
    QMenu *m = new QMenu(__("project", "menubar"), this);
    m->addAction(__("reload", "menubar"), parent(), SLOT(onMenuBarProjectReload()));
    m->addSeparator();
    m->addAction(__("build", "menubar"), parent(), SLOT(onMenuBarProjectBuild()), Qt::Key_F5);
    m->addSeparator();
    m->addAction(__("sign_export", "menubar"), parent(), SLOT(onMenuBarProjectSignExport()));
    m->addAction(__("install", "menubar"), parent(), SLOT(onMenuBarProjectInstall()));
    m->addSeparator();
    m->addAction(__("browse", "menubar"), parent(), SLOT(onMenuBarProjectBrowseFiles()));
    addAction(m->menuAction());
}

MenuBar::~MenuBar()
{
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
