#include "include/textutils.h"

QString TextUtils::ltrim(const QString& str, const QChar &chr)
{
    QString t(str);
    while (t.at(0) == chr)
    {
        t = t.mid(1);
    }
    return t;
}

QString TextUtils::rtrim(const QString& str, const QChar &chr)
{
    QString t(str);
    int l = t.size() - 1;
    while ((l >= 0) && (t.at(l) == chr))
    {
        t = str.left(l);
        l--;
    }
    return t;
}
