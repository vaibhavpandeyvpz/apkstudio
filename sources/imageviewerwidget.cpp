#include <QScrollBar>
#include "imageviewerwidget.h"

ImageViewerWidget::ImageViewerWidget(QWidget *parent) :
    QScrollArea(parent), m_Scale(1.0)
{
    m_FlickCharm = new FlickCharm(this);
    m_FlickCharm->activateOn(this);
    m_Image = new QLabel(this);
    m_Image->setBackgroundRole(QPalette::Base);
    m_Image->setScaledContents(true);
    m_Image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_Image->setStyleSheet("QLabel {"
        "background-color: transparent;"
        "background-image: url(':/images/checkerboard.png');"
        "border: 1px dashed #000000;"
    "}");
    setAlignment(Qt::AlignCenter);
    setBackgroundRole(QPalette::Dark);
    setWidget(m_Image);
    viewport()->setCursor(Qt::OpenHandCursor);
}

QString ImageViewerWidget::filePath()
{
    return m_FilePath;
}

void ImageViewerWidget::open(const QString &path)
{
    m_FilePath = path;
    m_Image->setPixmap(QPixmap(path));
}

void ImageViewerWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers().testFlag(Qt::ControlModifier)) {
        if ((event->key() == Qt::Key_Minus) || (event->key() == Qt::Key_ZoomOut)) {
            zoomOut();
        } else if ((event->key() == Qt::Key_Plus) || (event->key() == Qt::Key_Equal) || (event->key() == Qt::Key_ZoomIn)) {
            zoomIn();
        }
    }
    QScrollArea::keyPressEvent(event);
}

void ImageViewerWidget::zoomIn()
{
    zoomInOut(1.25);
}

void ImageViewerWidget::zoomInOut(const double f)
{
    m_Scale *= f;
    m_Image->resize(m_Scale * m_Image->pixmap().size());
    QScrollBar *hbar = horizontalScrollBar();
    QScrollBar *vbar = verticalScrollBar();
    int hs = int(f * hbar->value() + ((f - 1) * hbar->pageStep() / 2));
    int vs = int(f * vbar->value() + ((f - 1) * vbar->pageStep() / 2));
    hbar->setValue(hs);
    vbar->setValue(vs);
}

void ImageViewerWidget::zoomOut()
{
    zoomInOut(0.75);
}

void ImageViewerWidget::zoomReset()
{
    m_Image->adjustSize();
    zoomInOut(1.0);
    QScrollBar *hbar = horizontalScrollBar();
    QScrollBar *vbar = verticalScrollBar();
    hbar->setValue(int(hbar->maximum() / 2));
    vbar->setValue(int(vbar->maximum() / 2));
}
