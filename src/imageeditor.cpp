#include "imageeditor.h"

void ImageEditor::center()
{
    QScrollBar *horizontal = horizontalScrollBar();
    QScrollBar *vertical = verticalScrollBar();
    horizontal->setValue(int(horizontal->maximum() / 2));
    vertical->setValue(int(vertical->maximum() / 2));
}

void ImageEditor::invalidate(double factor)
{
    QScrollBar *horizontal = horizontalScrollBar();
    QScrollBar *vertical = verticalScrollBar();
    int hscroll = int(factor * horizontal->value() + ((factor - 1) * horizontal->pageStep() / 2));
    horizontal->setValue(hscroll);
    int vscroll = int(factor * vertical->value() + ((factor - 1) * vertical->pageStep() / 2));
    vertical->setValue(vscroll);
}

void ImageEditor::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers().testFlag(Qt::ControlModifier)) {
        if ((event->key() == Qt::Key_Minus))
            zoomOut();
        else if ((event->key() == Qt::Key_Equal) || (event->key() == Qt::Key_Plus))
            zoomIn();
        else if (event->modifiers().testFlag(Qt::ShiftModifier) && event->key() == Qt::Key_Z)
            revert();
    }
}

bool ImageEditor::open(const QFile &file, bool replace)
{
    if (!file.exists())
        return false;
    QString path = file.fileName();
    QImage image(path);
    _image->setPixmap(QPixmap::fromImage(image));
    _image->adjustSize();
    if (!replace)
        _current = _original = path;
    else
        _current = path;
    center();
    return true;
}

void ImageEditor::revert()
{
    _scale = 1.0;
    zoom(1.0);
    center();
}

bool ImageEditor::save()
{
    if (_current.compare(_original) == 0)
        return true;
    if (QFile::exists(_original))
        QFile::remove(_original);
    return QFile::copy(_current, _original);
}

void ImageEditor::zoom(const double factor)
{
    _scale *= factor;
    _image->resize(_scale * _image->pixmap()->size());
    invalidate(factor);
    // zoomInAct->setEnabled(_scale < 3.0);
    // zoomOutAct->setEnabled(_scale > 0.333);
}
