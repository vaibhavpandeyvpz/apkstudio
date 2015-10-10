#include <QIcon>
#include "qrc.h"
#include "toolbar.h"

APP_NAMESPACE_START

ToolBar::ToolBar(QWidget *p)
    : QToolBar(p)
{
    addAction(Qrc::icon("toolbar_apk"), Qrc::text("toolbar.item.apk"), p, SLOT(onMenuBarFileOpenApk()));
    addAction(Qrc::icon("toolbar_dir"), Qrc::text("toolbar.item.dir"), p, SLOT(onMenuBarFileOpenDir()));
    addSeparator();
    addAction(Qrc::icon("toolbar_save"), Qrc::text("toolbar.item.save"), p, SLOT(onMenuBarFileSave()));
    addSeparator();
    addAction(Qrc::icon("toolbar_build"), Qrc::text("toolbar.item.build"), p, SLOT(onMenuBarProjectBuild()));
    addAction(Qrc::icon("toolbar_sign"), Qrc::text("toolbar.item.sign"), p, SLOT(onMenuBarProjectSignExport()));
    addSeparator();
    addAction(Qrc::icon("toolbar_terminal"), Qrc::text("toolbar.item.terminal"), p, SLOT(onMenuBarFileTerminal()));
    addAction(Qrc::icon("toolbar_settings"), Qrc::text("toolbar.item.settings"), p, SLOT(onMenuBarEditSettings()));
    setObjectName("ToolBar");
}

APP_NAMESPACE_END
