#include "apktool.h"
#include "java.h"
#include "javadock.h"
#include "qrc.h"

AS_NAMESPACE_START

JavaDock::JavaDock(QWidget *parent)
    : ConsoleDock(Qrc::text("dock.java.title"), "java", parent)
{
    setContentsMargins(2, 2, 2, 2);
    setObjectName("JavaDock");
    _connections << connect(ApkTool::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(ApkTool::get(), &Process::executing, this, &ConsoleDock::onExecuting);
    _connections << connect(Java::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(Java::get(), &Process::executing, this, &ConsoleDock::onExecuting);
}

AS_NAMESPACE_END
