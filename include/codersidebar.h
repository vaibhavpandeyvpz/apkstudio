#ifndef CODERLINENUMBERS_H
#define CODERLINENUMBERS_H

#include <QApplication>
#include <QWidget>
#include "macros.h"

APP_NAMESPACE_START

class Coder;

class CoderSidebar : public QWidget
{
    Q_OBJECT
private:
    Coder *_coder;
protected:
    void leaveEvent(QEvent *event);
    void mouseEvent(QMouseEvent *event);
    inline void mouseMoveEvent(QMouseEvent *event)
    {
        mouseEvent(event);
    }
    inline void mousePressEvent(QMouseEvent *event)
    {
        mouseEvent(event);
    }
    inline void mouseReleaseEvent(QMouseEvent *event)
    {
        mouseEvent(event);
    }
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
public:
    explicit CoderSidebar(Coder *coder);
    QSize sizeHint() const;
};

APP_NAMESPACE_END

#endif // CODERLINENUMBERS_H
