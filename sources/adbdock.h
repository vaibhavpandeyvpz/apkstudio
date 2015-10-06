#ifndef ADBDOCK_H
#define ADBDOCK_H

#include "consoledock.h"

AS_NAMESPACE_START

class AdbDock : public ConsoleDock
{
    Q_OBJECT
public:
    explicit AdbDock(QWidget *parent = 0);
};

AS_NAMESPACE_END

#endif // ADBDOCK_H
