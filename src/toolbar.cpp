#include <QIcon>
#include "include/qrc.h"
#include "include/toolbar.h"

APP_NAMESPACE_START

ToolBar::ToolBar(QWidget *p)
    : QToolBar(p)
{
    addAction(Qrc::icon("toolbar_apk"), __("apk", "toolbar"), p, SLOT(onMenuBarFileOpenApk()));
    addAction(Qrc::icon("toolbar_dir"), __("directory", "toolbar"), p, SLOT(onMenuBarFileOpenDir()));
    addSeparator();
    addAction(Qrc::icon("toolbar_save"), __("save", "toolbar"), p, SLOT(onMenuBarFileSave()));
    addSeparator();
    addAction(Qrc::icon("toolbar_build"), __("build", "toolbar"), p, SLOT(onMenuBarProjectBuild()));
    addAction(Qrc::icon("toolbar_sign"), __("sign", "toolbar"), p, SLOT(onToolBarProjectSign()));
    addAction(Qrc::icon("toolbar_install"), __("install", "toolbar"), p, SLOT(onMenuBarProjectInstall()));
    addSeparator();
    addAction(Qrc::icon("toolbar_terminal"), __("terminal", "toolbar"), p, SLOT(onMenuBarFileTerminal()));
    addAction(Qrc::icon("toolbar_settings"), __("settings", "toolbar"), p, SLOT(onMenuBarEditSettings()));
    setObjectName("ToolBar");
}

APP_NAMESPACE_END
