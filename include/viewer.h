#ifndef VIEWER_H
#define VIEWER_H

#include <QAction>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QMenu>
#include <QPixmap>
#include <QScrollArea>
#include <QScrollBar>
#include "macros.h"

APP_NAMESPACE_START

class FlickCharm;

class Viewer : public QScrollArea
{
    Q_OBJECT
private:
    APP_CONNECTIONS_LIST
    FlickCharm *_flickCharm;
    QLabel *_image;
    double _scale;
private:
    void scrollFix();
    void zoomInOut(const double factor);
protected:
    void keyPressEvent(QKeyEvent *event);
public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();
public:
    inline void setPixmap(const QPixmap &i) { _image->setPixmap(i); }
    inline void zoomIn() { zoomInOut(1.25); }
    inline void zoomOut() { zoomInOut(0.8); }
    void zoomReset();
};

APP_NAMESPACE_END

#endif // VIEWER_H
