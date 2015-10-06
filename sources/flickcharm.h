#ifndef FLICKCHARM_H
#define FLICKCHARM_H

#include <QObject>
#include "macros.h"

class QWidget;

AS_NAMESPACE_START

class FlickCharmPrivate;

class FlickCharm: public QObject
{
    Q_OBJECT
public:
    FlickCharm(QObject *parent = 0);
    ~FlickCharm();
    void activateOn(QWidget *widget);
    void deactivateFrom(QWidget *widget);
    bool eventFilter(QObject *object, QEvent *event);
protected:
    void timerEvent(QTimerEvent *event);
private:
    FlickCharmPrivate *d;
};

AS_NAMESPACE_END

#endif // FLICKCHARM_H
