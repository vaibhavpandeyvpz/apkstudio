#ifndef JAVADOCK_H
#define JAVADOCK_H

#include "consoledock.h"

AS_NAMESPACE_START

class JavaDock : public ConsoleDock
{
    Q_OBJECT
public:
    explicit JavaDock(QWidget *parent = 0);
};

AS_NAMESPACE_END

#endif // JAVADOCK_H
