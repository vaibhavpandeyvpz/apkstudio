#include "include/flickcharm.h"
#include "include/viewer.h"

APP_NAMESPACE_START

Viewer::Viewer(QWidget *parent) :
    QScrollArea(parent), _scale(1.0)
{
    _flickCharm = new FlickCharm(this);
    _flickCharm->activateOn(this);
    _image = new QLabel(this);
    _image->setBackgroundRole(QPalette::Base);
    _image->setScaledContents(true);
    _image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _image->setStyleSheet("QLabel {"
        "background-color: transparent;"
        "background-image: url(':/images/viewer_bg.png');"
        "border: 1px dashed #000000;"
    "}");
    setAlignment(Qt::AlignCenter);
    setBackgroundRole(QPalette::Dark);
    setWidget(_image);
    viewport()->setCursor(Qt::OpenHandCursor);
}

void Viewer::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers().testFlag(Qt::ControlModifier))
    {
        if ((event->key() == Qt::Key_Minus) || (event->key() == Qt::Key_ZoomOut)) { zoomOut(); }
        else if ((event->key() == Qt::Key_Plus) || (event->key() == Qt::Key_Equal) || (event->key() == Qt::Key_ZoomIn)) { zoomIn(); }
    }
    QScrollArea::keyPressEvent(event);
}

void Viewer::zoomInOut(const double f)
{
    _scale *= f;
    _image->resize(_scale * _image->pixmap()->size());
    QScrollBar *hbar = horizontalScrollBar();
    QScrollBar *vbar = verticalScrollBar();
    int hs = int(f * hbar->value() + ((f - 1) * hbar->pageStep() / 2));
    int vs = int(f * vbar->value() + ((f - 1) * vbar->pageStep() / 2));
    hbar->setValue(hs);
    vbar->setValue(vs);
}

void Viewer::zoomReset()
{
    _image->adjustSize();
    zoomInOut(1.0);
    QScrollBar *hbar = horizontalScrollBar();
    QScrollBar *vbar = verticalScrollBar();
    hbar->setValue(int(hbar->maximum() / 2));
    vbar->setValue(int(vbar->maximum() / 2));
}

Viewer::~Viewer()
{
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
