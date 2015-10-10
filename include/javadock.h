#ifndef JAVADOCK_H
#define JAVADOCK_H

#include "consoledock.h"

APP_NAMESPACE_START

class JavaDock : public ConsoleDock
{
    Q_OBJECT
public:
    explicit JavaDock(QWidget *parent = 0);
};

APP_NAMESPACE_END

#endif // JAVADOCK_H
