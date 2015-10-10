#include "jarsigner.h"
#include "jarsignerdock.h"
#include "qrc.h"

APP_NAMESPACE_START

JarSignerDock::JarSignerDock(QWidget *parent)
    : ConsoleDock(Qrc::text("dock.jarsigner.title"), "jarsigner", parent)
{
    setContentsMargins(2, 2, 2, 2);
    setObjectName("JarSignerDock");
    _connections << connect(JarSigner::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(JarSigner::get(), &Process::executing, this, &ConsoleDock::onExecuting);
}

APP_NAMESPACE_END
