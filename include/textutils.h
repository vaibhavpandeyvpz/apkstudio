#ifndef TEXTUTILS_H
#define TEXTUTILS_H

#include <QString>
#include "macros.h"

class TextUtils
{
public:
    static QString ltrim(const QString& str, const QChar& c = QChar::Space);
    static QString rtrim(const QString& str, const QChar& c = QChar::Space);
};

#endif // TEXTUTILS_H
