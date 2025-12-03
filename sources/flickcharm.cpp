#include <QAbstractScrollArea>
#include <QApplication>
#include <QBasicTimer>
#include <QEvent>
#include <QHash>
#include <QList>
#include <QMouseEvent>
#include <QScrollBar>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QPointingDevice>
#endif
#include "flickcharm.h"

FlickCharm::FlickCharm(QObject *parent): QObject(parent)
{
    d = new FlickCharmPrivate;
}

FlickCharm::~FlickCharm()
{
    delete d;
}

void FlickCharm::activateOn(QWidget *widget)
{
    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        QWidget *viewport = scrollArea->viewport();
        viewport->installEventFilter(this);
        scrollArea->installEventFilter(this);
        d->flickData.remove(viewport);
        d->flickData[viewport] = new FlickData;
        d->flickData[viewport]->widget = widget;
        d->flickData[viewport]->state = FlickData::Steady;
        return;
    }
}

void FlickCharm::deactivateFrom(QWidget *widget)
{
    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        QWidget *viewport = scrollArea->viewport();
        viewport->removeEventFilter(this);
        scrollArea->removeEventFilter(this);
        delete d->flickData[viewport];
        d->flickData.remove(viewport);
        return;
    }
}

static QPoint scrollOffset(QWidget *widget)
{
    int x = 0, y = 0;
    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        x = scrollArea->horizontalScrollBar()->value();
        y = scrollArea->verticalScrollBar()->value();
    }
    return QPoint(x, y);
}

static void setScrollOffset(QWidget *widget, const QPoint &p)
{
    QAbstractScrollArea *scrollArea = dynamic_cast<QAbstractScrollArea*>(widget);
    if (scrollArea) {
        scrollArea->horizontalScrollBar()->setValue(p.x());
        scrollArea->verticalScrollBar()->setValue(p.y());
    }
}

static QPoint deaccelerate(const QPoint &speed, int a = 1, int max = 64)
{
    int x = qBound(-max, speed.x(), max);
    int y = qBound(-max, speed.y(), max);
    x = (x == 0) ? x : (x > 0) ? qMax(0, x - a) : qMin(0, x + a);
    y = (y == 0) ? y : (y > 0) ? qMax(0, y - a) : qMin(0, y + a);
    return QPoint(x, y);
}

bool FlickCharm::eventFilter(QObject *object, QEvent *event)
{
    if (!object->isWidgetType()) {
        return false;
    }
    QEvent::Type type = event->type();
    if (type != QEvent::MouseButtonPress && type != QEvent::MouseButtonRelease && type != QEvent::MouseMove) {
        return false;
    }
    QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
    if (!mouseEvent || mouseEvent->modifiers() != Qt::NoModifier) {
        return false;
    }
    QWidget *viewport = dynamic_cast<QWidget*>(object);
    FlickData *data = d->flickData.value(viewport);
    if (!viewport || !data || data->ignored.removeAll(event)) {
        return false;
    }
    bool consumed = false;
    switch (data->state) {
    case FlickData::Steady:
        if (mouseEvent->type() == QEvent::MouseButtonPress) {
            if (mouseEvent->buttons() == Qt::LeftButton) {
                consumed = true;
                data->state = FlickData::Pressed;
                data->pressPos = mouseEvent->pos();
                data->offset = scrollOffset(data->widget);
            }
        }
        break;
    case FlickData::Pressed:
        if (mouseEvent->type() == QEvent::MouseButtonRelease) {
            consumed = true;
            data->state = FlickData::Steady;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            QMouseEvent *event1 = new QMouseEvent(QEvent::MouseButtonPress, QPointF(data->pressPos), data->pressPos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, QPointingDevice::primaryPointingDevice());
            QMouseEvent *event2 = new QMouseEvent(mouseEvent->type(), QPointF(mouseEvent->pos()), mouseEvent->globalPos(), mouseEvent->button(), mouseEvent->buttons(), mouseEvent->modifiers(), QPointingDevice::primaryPointingDevice());
#else
            QMouseEvent *event1 = new QMouseEvent(QEvent::MouseButtonPress, data->pressPos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
            QMouseEvent *event2 = new QMouseEvent(*mouseEvent);
#endif
            data->ignored << event1;
            data->ignored << event2;
            QApplication::postEvent(object, event1);
            QApplication::postEvent(object, event2);
        }
        if (mouseEvent->type() == QEvent::MouseMove) {
            consumed = true;
            data->state = FlickData::ManualScroll;
            data->dragPos = QCursor::pos();
            if (!d->ticker.isActive()) {
                d->ticker.start(20, this);
            }
        }
        break;
    case FlickData::ManualScroll:
        if (mouseEvent->type() == QEvent::MouseMove) {
            consumed = true;
            QPoint delta = mouseEvent->pos() - data->pressPos;
            setScrollOffset(data->widget, data->offset - delta);
        }
        if (mouseEvent->type() == QEvent::MouseButtonRelease) {
            consumed = true;
            data->state = FlickData::AutoScroll;
        }
        break;
    case FlickData::AutoScroll:
        if (mouseEvent->type() == QEvent::MouseButtonPress) {
            consumed = true;
            data->state = FlickData::Stop;
            data->speed = QPoint(0, 0);
            data->pressPos = mouseEvent->pos();
            data->offset = scrollOffset(data->widget);
        }
        if (mouseEvent->type() == QEvent::MouseButtonRelease) {
            consumed = true;
            data->state = FlickData::Steady;
            data->speed = QPoint(0, 0);
        }
        break;
    case FlickData::Stop:
        if (mouseEvent->type() == QEvent::MouseButtonRelease) {
            consumed = true;
            data->state = FlickData::Steady;
        }
        if (mouseEvent->type() == QEvent::MouseMove) {
            consumed = true;
            data->state = FlickData::ManualScroll;
            data->dragPos = QCursor::pos();
            if (!d->ticker.isActive()) {
                d->ticker.start(20, this);
            }
        }
        break;
    }
    return consumed;
}

void FlickCharm::timerEvent(QTimerEvent *event)
{
    int count = 0;
    QHashIterator<QWidget*, FlickData*> item(d->flickData);
    while (item.hasNext()) {
        item.next();
        FlickData *data = item.value();
        if (data->state == FlickData::ManualScroll) {
            count++;
            data->speed = QCursor::pos() - data->dragPos;
            data->dragPos = QCursor::pos();
        }
        if (data->state == FlickData::AutoScroll) {
            count++;
            data->speed = deaccelerate(data->speed);
            QPoint p = scrollOffset(data->widget);
            setScrollOffset(data->widget, p - data->speed);
            if (data->speed == QPoint(0, 0))
                data->state = FlickData::Steady;
        }
    }
    if (!count) {
        d->ticker.stop();
    }
    QObject::timerEvent(event);
}
