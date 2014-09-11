#ifndef IACTION_H
#define IACTION_H

#include <QObject>

class IAction
{
public:
    virtual void onActionRestart() = 0;
    virtual void onActionQuit() = 0;
};

Q_DECLARE_INTERFACE(IAction, "IAction/0.1")

#endif // IACTION_H
