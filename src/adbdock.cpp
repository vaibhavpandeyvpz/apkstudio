#include "adb.h"
#include "adbdock.h"
#include "qrc.h"

APP_NAMESPACE_START

AdbDock::AdbDock(QWidget *parent)
    : ConsoleDock(Qrc::text("dock.adb.title"), "adb", parent)
{
    setContentsMargins(2, 2, 2, 2);
    setObjectName("AdbDock");
    _connections << connect(Adb::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(Adb::get(), &Process::executing, this, &ConsoleDock::onExecuting);
}

APP_NAMESPACE_END
