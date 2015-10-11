#include <QIcon>
#include "include/qrc.h"

APP_NAMESPACE_START

QString Qrc::text(const char *t, const char* c)
{
    return QApplication::translate(c, t);
}

QIcon Qrc::icon(const QString &n)
{
    return QIcon(QString(QRC_ICONS).arg(n));
}

QPixmap Qrc::image(const QString &n, const QString &e)
{
    return QPixmap(QString(QRC_IMAGES).arg(n).arg(e));
}

APP_NAMESPACE_END
