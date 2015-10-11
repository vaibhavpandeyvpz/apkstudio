#include "include/dialog.h"

APP_NAMESPACE_START

Dialog::Dialog(const QString &t, QWidget *p)
    : QDialog(p)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    setMinimumSize(320, 240);
#ifdef Q_OS_WIN
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
    setWindowTitle(t);
}

Dialog::~Dialog()
{
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
