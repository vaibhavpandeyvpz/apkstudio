#ifndef ZIPALIGN_H
#define ZIPALIGN_H

#include "macros.h"
#include "process.h"

APP_NAMESPACE_START

class ZipAlign : public Process
{
private:
    static ZipAlign *_self;
private:
    explicit ZipAlign(QObject *parent = 0);
public:
    Result align(const QString &src, const QString &dest);
    static ZipAlign *get();
};

APP_NAMESPACE_END

#endif // ZIPALIGN_H
