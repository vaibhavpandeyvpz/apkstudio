#include <QIcon>
#include "constants.h"
#include "qrc.h"

AS_NAMESPACE_START

QString Qrc::text(const char *t)
{
    return QApplication::translate(TRANSLATION_CONTEXT, t);
}

QIcon Qrc::icon(const QString &n)
{
    return QIcon(QString(QRC_ICONS).arg(n));
}

QPixmap Qrc::image(const QString &n, const QString &e)
{
    return QPixmap(QString(QRC_IMAGES).arg(n).arg(e));
}

AS_NAMESPACE_END
