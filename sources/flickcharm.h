#ifndef FLICKCHARM_H
#define FLICKCHARM_H

#include <QBasicTimer>
#include <QHash>
#include <QObject>
#include <QPoint>

class QWidget;

struct FlickData
{
    typedef enum
    {
        Steady,
        Pressed,
        ManualScroll,
        AutoScroll,
        Stop
    } State;
    State state;
    QWidget *widget;
    QPoint pressPos;
    QPoint offset;
    QPoint dragPos;
    QPoint speed;
    QList<QEvent*> ignored;
};

class FlickCharmPrivate
{
public:
    QHash<QWidget*, FlickData*> flickData;
    QBasicTimer ticker;
};

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

#endif // FLICKCHARM_H
