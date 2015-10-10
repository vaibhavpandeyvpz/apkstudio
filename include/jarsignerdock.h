#ifndef JARSIGNERDOCK_H
#define JARSIGNERDOCK_H

#include "consoledock.h"

APP_NAMESPACE_START

class JarSignerDock : public ConsoleDock
{
    Q_OBJECT
public:
    explicit JarSignerDock(QWidget *parent = 0);
};

APP_NAMESPACE_END

#endif // JARSIGNERDOCK_H
