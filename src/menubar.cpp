#include <QDir>
#include "menubar.h"
#include "preferences.h"
#include "qrc.h"
#include "runner.h"

APP_NAMESPACE_START

MenuBar::MenuBar(QWidget *p)
    : QMenuBar(p)
{
    addFileMenu();
    addEditMenu();
    addProjectMenu();
    addHelpMenu();
    _connections << connect(this, SIGNAL(projectOpen(QString)), p, SLOT(onMenuBarFileOpenDirProxy(QString)));
}

void MenuBar::addEditMenu()
{
    QMenu *m = new QMenu(Qrc::text("menubar.edit"), this);
    m->addAction(Qrc::text("menubar.edit.undo"), parent(), SLOT(onMenuBarEditUndo()), QKeySequence::Undo);
    m->addAction(Qrc::text("menubar.edit.redo"), parent(), SLOT(onMenuBarEditRedo()), QKeySequence::Redo);
    m->addSeparator();
    m->addAction(Qrc::text("menubar.edit.cut"), parent(), SLOT(onMenuBarEditCut()), QKeySequence::Cut);
    m->addAction(Qrc::text("menubar.edit.copy"), parent(), SLOT(onMenuBarEditCopy()), QKeySequence::Copy);
    m->addAction(Qrc::text("menubar.edit.paste"), parent(), SLOT(onMenuBarEditPaste()), QKeySequence::Paste);
    m->addSeparator();
    m->addAction(Qrc::text("menubar.edit.find"), parent(), SLOT(onMenuBarEditFind()), QKeySequence::Find);
    m->addAction(Qrc::text("menubar.edit.replace"), parent(), SLOT(onMenuBarEditReplace()), QKeySequence::Replace);
    m->addAction(Qrc::text("menubar.edit.goto"), parent(), SLOT(onMenuBarEditGoto()));
    m->addSeparator();
    m->addAction(Qrc::text("menubar.edit.settings"), parent(), SLOT(onMenuBarEditSettings()), QKeySequence::Preferences);
    addAction(m->menuAction());
}

void MenuBar::addFileMenu()
{
    QMenu *m = new QMenu(Qrc::text("menubar.file"), this);
    QMenu *o = new QMenu(Qrc::text("menubar.file.open"), m);
    o->addAction(Qrc::text("menubar.file.open.apk"), parent(), SLOT(onMenuBarFileOpenApk()), QKeySequence::New);
    o->addAction(Qrc::text("menubar.file.open.dir"), parent(), SLOT(onMenuBarFileOpenDir()), QKeySequence::Open);
    o->addSeparator();
    o->addAction(Qrc::text("menubar.file.open.file"), parent(), SLOT(onMenuBarFileOpenFile()));
    m->addAction(o->menuAction());
    m->addSeparator();
    m->addAction(Qrc::text("menubar.file.close"), parent(), SLOT(onMenuBarFileClose()), QKeySequence::Close);
    m->addAction(Qrc::text("menubar.file.close_all"), parent(), SLOT(onMenuBarFileCloseAll()));
    m->addSeparator();
    m->addAction(Qrc::text("menubar.file.save"), parent(), SLOT(onMenuBarFileSave()), QKeySequence::Save);
    m->addAction(Qrc::text("menubar.file.save_all"), parent(), SLOT(onMenuBarFileSaveAll()));
    m->addSeparator();
    QDir dir(Preferences::get()->previousProject());
    if (dir.exists() && dir.exists("apktool.yml"))
    {
        _connections << connect(m->addAction(dir.dirName()), &QAction::triggered, [=]
        {
            emit projectOpen(dir.absolutePath());
        });
    }
    else
    {
        m->addAction(Qrc::text("menubar.file.recent_none"))->setEnabled(false);
    }
    m->addSeparator();
    m->addAction(Qrc::text("menubar.file.terminal"), parent(), SLOT(onMenuBarFileTerminal()));
    m->addSeparator();
    m->addAction(Qrc::text("menubar.file.quit"), parent(), SLOT(onMenuBarFileQuit()), QKeySequence::Quit);
    addAction(m->menuAction());
}

void MenuBar::addHelpMenu()
{
    QMenu *m = new QMenu(Qrc::text("menubar.help"), this);
    m->addAction(Qrc::text("menubar.help.about"), parent(), SLOT(onMenuBarHelpAbout()));
    m->addAction(Qrc::text("menubar.help.documentation"), parent(), SLOT(onMenuBarHelpDocumentation()));
    m->addSeparator();
    QMenu *f = new QMenu(Qrc::text("menubar.help.feedback"), m);
    f->addAction(Qrc::text("menubar.help.feedback.thanks"), parent(), SLOT(onMenuBarHelpFeedbackThanks()));
    f->addAction(Qrc::text("menubar.help.feedback.issues"), parent(), SLOT(onMenuBarHelpFeedbackIssues()));
    m->addAction(f->menuAction());
    m->addAction(Qrc::text("menubar.help.contribute"), parent(), SLOT(onMenuBarHelpContribute()));
    m->addSeparator();
    addAction(m->menuAction());
}

void MenuBar::addProjectMenu()
{
    QMenu *m = new QMenu(Qrc::text("menubar.project"), this);
    m->addAction(Qrc::text("menubar.project.reload"), parent(), SLOT(onMenuBarProjectReload()));
    m->addSeparator();
    m->addAction(Qrc::text("menubar.project.build"), parent(), SLOT(onMenuBarProjectBuild()), Qt::Key_F5);
    m->addSeparator();
    m->addAction(Qrc::text("menubar.project.sign_export"), parent(), SLOT(onMenuBarProjectSignExport()));
    m->addAction(Qrc::text("menubar.project.install"), parent(), SLOT(onMenuBarProjectInstall()));
    addAction(m->menuAction());
}

MenuBar::~MenuBar()
{
    AS_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
