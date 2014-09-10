#include "utility.h"

QString Utility::capitalize(const QString &text, bool strict)
{
    QString temporary = text;
    if (strict)
        temporary = text.toLower();
    temporary[0] = temporary[0].toUpper();
    return temporary;
}

QIcon Utility::icon(const char *name)
{
    return QIcon(QString(RESOURCE_PATH_ICON).append(name).append(".png"));
}

QString Utility::size(float bytes)
{
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";
    QStringListIterator iterator(list);
    QString unit("B");
    while ((bytes >= 1024.0) && iterator.hasNext()) {
        unit = iterator.next();
        bytes /= 1024.0;
    }
    return QString().setNum(bytes, 'f', 2) + ' ' + unit;
}

QString Utility::timestamp(const QDateTime &date, const QString &format)
{
    return date.toString(format);
}

QString Utility::translate(const char *context, const char *key)
{
    return QApplication::translate(context, key);
}
