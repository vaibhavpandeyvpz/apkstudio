#ifndef IMAGEVIEWERWIDGET_H
#define IMAGEVIEWERWIDGET_H

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
#include "flickcharm.h"

class ImageViewerWidget : public QScrollArea
{
    Q_OBJECT
private:
    FlickCharm *m_FlickCharm;
    QLabel *m_Image;
    double m_Scale;
private:
    void scrollFix();
    void zoomInOut(const double factor);
protected:
    void keyPressEvent(QKeyEvent *event);
public:
    explicit ImageViewerWidget(QWidget *parent = nullptr);
public:
    inline void setPixmap(const QPixmap &i) { m_Image->setPixmap(i); }
    inline void zoomIn() { zoomInOut(1.25); }
    inline void zoomOut() { zoomInOut(0.8); }
    void zoomReset();
};

#endif // IMAGEVIEWERWIDGET_H
