#include "include/apktool.h"
#include "include/java.h"
#include "include/javadock.h"
#include "include/qrc.h"

APP_NAMESPACE_START

JavaDock::JavaDock(QWidget *parent)
    : ConsoleDock(__("java", "docks"), "java", parent)
{
    setContentsMargins(2, 2, 2, 2);
    setObjectName("JavaDock");
    _connections << connect(ApkTool::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(ApkTool::get(), &Process::executing, this, &ConsoleDock::onExecuting);
    _connections << connect(Java::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(Java::get(), &Process::executing, this, &ConsoleDock::onExecuting);
}

APP_NAMESPACE_END
