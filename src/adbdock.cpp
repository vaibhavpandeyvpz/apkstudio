#include "include/adb.h"
#include "include/adbdock.h"
#include "include/qrc.h"

APP_NAMESPACE_START

AdbDock::AdbDock(QWidget *parent)
    : ConsoleDock(__("adb", "docks"), "adb", parent)
{
    setContentsMargins(2, 2, 2, 2);
    setObjectName("AdbDock");
    _connections << connect(Adb::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(Adb::get(), &Process::executing, this, &ConsoleDock::onExecuting);
}

APP_NAMESPACE_END
