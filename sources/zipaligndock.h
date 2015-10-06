#ifndef ZIPALIGNDOCK_H
#define ZIPALIGNDOCK_H

#include "consoledock.h"

AS_NAMESPACE_START

class ZipAlignDock : public ConsoleDock
{
    Q_OBJECT
public:
    explicit ZipAlignDock(QWidget *parent = 0);
};

AS_NAMESPACE_END

#endif // ZIPALIGNDOCK_H
