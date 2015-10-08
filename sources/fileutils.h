#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QIcon>
#include "constants.h"
#include "macros.h"
#include "qrc.h"

AS_NAMESPACE_START

class FileUtils
{
public:
    static QString read(const QString &path);
    static bool rimraf(const QString &dir);
    static void show(const QString &p);
};

AS_NAMESPACE_END

#endif // FILEUTILS_H
