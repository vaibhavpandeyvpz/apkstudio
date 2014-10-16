#include "format.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

QString Format::size(float bytes)
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

QString Format::timestamp(const QDateTime &date, const QString &format)
{
    return date.toString(format);
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
