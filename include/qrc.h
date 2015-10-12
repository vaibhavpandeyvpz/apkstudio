#ifndef QRC_H
#define QRC_H

#include <QApplication>
#include "constants.h"
#include "macros.h"

APP_NAMESPACE_START

class Qrc
{
public:
    static QString text(const char *text, const char* context = TRANSLATION_CONTEXT);
    static QIcon icon(const QString &name);
    static QPixmap image(const QString &name, const QString &ext = QString("png"));
};

inline QString __(const char* text, const char* context)
{
    return Qrc::text(text, context);
}

inline QString __(const char* text, const char* context, const QString arg1)
{
    return __(text, context).arg(arg1);
}

inline QString __(const char* text, const char* context, const QString arg1, const QString arg2)
{
    return __(text, context, arg1).arg(arg2);
}

APP_NAMESPACE_END

#endif // QRC_H
