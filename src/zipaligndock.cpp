#include "include/zipalign.h"
#include "include/zipaligndock.h"
#include "include/qrc.h"

APP_NAMESPACE_START

ZipAlignDock::ZipAlignDock(QWidget *parent)
    : ConsoleDock(__("zip_align", "docks"), "zipalign", parent)
{
    setContentsMargins(2, 2, 2, 2);
    setObjectName("ZipAlignDock");
    _connections << connect(ZipAlign::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(ZipAlign::get(), &Process::executing, this, &ConsoleDock::onExecuting);
}

APP_NAMESPACE_END
