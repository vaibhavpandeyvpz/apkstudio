#ifndef IMAGEVIEWERWIDGET_H
#define IMAGEVIEWERWIDGET_H

#include <QKeyEvent>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include "flickcharm.h"

class ImageViewerWidget : public QScrollArea
{
    Q_OBJECT
private:
    QString m_FilePath;
    FlickCharm *m_FlickCharm;
    QLabel *m_Image;
    double m_Scale;
public:
    explicit ImageViewerWidget(QWidget *parent = nullptr);
    QString filePath();
    void open(const QString &path);
    void zoomIn();
    void zoomOut();
    void zoomReset();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    void scrollFix();
    void zoomInOut(const double factor);
};

#endif // IMAGEVIEWERWIDGET_H
