#ifndef ASQRC
#define ASQRC

#include <QApplication>
#include "macros.h"

AS_NAMESPACE_START

class Qrc
{
public:
    static QString text(const char *text);
    static QIcon icon(const QString &name);
    static QPixmap image(const QString &name, const QString &ext = QString("png"));
};

AS_NAMESPACE_END

#endif // ASQRC
