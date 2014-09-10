#ifndef UTILITY_H
#define UTILITY_H

#include <QApplication>
#include <QDateTime>
#include <QIcon>

#include "constant.h"

class Utility
{
public:
    static QString capitalize(const QString &, bool = false);
    static QIcon icon(const char *);
    static QString size(float bytes);
    static QString timestamp(const QDateTime & = QDateTime::currentDateTime(), const QString & = FORMAT_TIMESTAMP_GENERAL);
    static QString translate(const char *, const char *);
};

#endif // UTILITY_H
