#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QIcon>
#include "constants.h"
#include "macros.h"

AS_NAMESPACE_START

class FileUtils
{
public:
    static QString read(const QString &path, const char *enc = ENCODING_DEFAULT);
    static bool rimraf(const QString &dir);
    static void show(const QString &p);
};

AS_NAMESPACE_END

#endif // FILEUTILS_H
