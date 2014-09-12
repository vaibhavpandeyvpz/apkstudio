#include "imageeditorui.h"

void ImageEditorUI::prepare()
{
    _charm = new FlickCharm(this);
    _charm->activateOn(this);
    _image = new QLabel(this);
    _image->setBackgroundRole(QPalette::Base);
    _image->setScaledContents(true);
    _image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _image->setStyleSheet("QLabel { background-color: " + Settings::imageBackground() + "; border: 1px solid rgba(0, 0, 0, 0.5); }");
    setAlignment(Qt::AlignCenter);
    setBackgroundRole(QPalette::Dark);
    viewport()->setCursor(Qt::OpenHandCursor);
    setStyleSheet(
    "QScrollArea {"
        "background-color: transparent;"
        "background-image: url(':/background/checkerboard.png');"
        "background-position: top left;"
        "background-repeat: repeat-xy;"
    "}"
    "QScrollArea:corner {"
        "background-color: #cccccc;"
    "}"
    );
    setWidget(_image);
}
