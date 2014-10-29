#include "viewer.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Viewer::Viewer(QWidget *parent) :
    QScrollArea(parent), scale(1.0)
{
    QMenu *context_menu = new QMenu(this);
    QAction *load = new QAction(icon("image"), translate("item_load"), context_menu);
    connections.append(connect(load, &QAction::triggered, [this] () {
        QString path = QFileDialog::getOpenFileName(this, translate("title_load"), "", QString("PNG Image Files (*.png)"));
        if (path.isNull() || path.isEmpty())
            return;
        this->open(path);
    }));
    QAction *revert = new QAction(icon("arrow_revert"), translate("item_revert"), context_menu);
    connections.append(connect(revert, &QAction::triggered, [this] () {
        this->open(this->path);
    }));
    QAction *save = new QAction(icon("disk"), translate("item_save"), context_menu);
    connections.append(connect(save, &QAction::triggered, [this] () {
        this->save();
    }));
    QAction *zoom_in = new QAction(icon("magnifier_plus"), translate("item_zoom_in"), context_menu);
    connections.append(connect(zoom_in, &QAction::triggered, [this] () {
        this->zoomIn();
    }));
    QAction *zoom_out = new QAction(icon("magnifier_minus"), translate("item_zoom_out"), context_menu);
    connections.append(connect(zoom_out, &QAction::triggered, [this] () {
        this->zoomOut();
    }));
    context_menu->addAction(zoom_in);
    context_menu->addAction(zoom_out);
    context_menu->addSeparator();
    context_menu->addAction(load);
    context_menu->addAction(save);
    context_menu->addSeparator();
    context_menu->addAction(revert);
    flick_charm = new FlickCharm(this);
    image = new QLabel(this);
    flick_charm->activateOn(this);
    image->setBackgroundRole(QPalette::Base);
    image->setScaledContents(true);
    image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    image->setStyleSheet(
        "QLabel {"
            "background-color: transparent;"
            "background-image: url(':/background/checkerboard.png');"
            "border: 1px dashed #000000;"
        "}"
    );
    connections.append(connect(this, &Viewer::customContextMenuRequested, [this, context_menu] (const QPoint &position) {
        context_menu->popup(this->viewport()->mapToGlobal(position));
    }));
    setAlignment(Qt::AlignCenter);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setBackgroundRole(QPalette::Dark);
    setFocus();
    setMinimumSize(160, 160);
    setStyleSheet(
        "QScrollArea {"
            "background-color: " + Settings::imageBackground() + ";"
            "background-position: top left;"
            "background-repeat: repeat-xy;"
        "}"
        "QScrollArea:corner {"
            "background-color: #cccccc;"
        "}"
    );
    setWidget(image);
    viewport()->setCursor(Qt::OpenHandCursor);
}

void Viewer::scrollfix()
{
    QScrollBar *horizontal = horizontalScrollBar();
    QScrollBar *vertical = verticalScrollBar();
    horizontal->setValue(int(horizontal->maximum() / 2));
    vertical->setValue(int(vertical->maximum() / 2));
}

void Viewer::keyPressEvent(QKeyEvent *event)
{
    if (!event->modifiers().testFlag(Qt::ControlModifier))
        goto inherited;
    if ((event->key() == Qt::Key_Minus))
        zoomOut();
    else if ((event->key() == Qt::Key_Equal) || (event->key() == Qt::Key_Plus))
        zoomIn();
    else if (event->modifiers().testFlag(Qt::ShiftModifier) && (event->key() == Qt::Key_Z))
        open(path);
    inherited:
    QScrollArea::keyPressEvent(event);
}

bool Viewer::open(const QFileInfo &info)
{
    if (path.isNull() || path.isEmpty())
        path = info.absoluteFilePath();
    image->setPixmap(QPixmap::fromImage(QImage(info.absoluteFilePath())));
    image->adjustSize();
    scale = 1.0;
    zoom(1.0);
    scrollfix();
    return true;
}

bool Viewer::save()
{
    QString path = QFileDialog::getSaveFileName(this, translate("title_save"), this->path, QString("PNG Image Files (*.png)"));
    if (path.isNull() || path.isEmpty())
        return false;
    if (QFile::exists(path))
        QFile::remove(path);
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    bool saved = image->pixmap()->save(&file, "PNG");
    file.close();
    return saved;
}

void Viewer::zoom(const double factor)
{
    scale *= factor;
    image->resize(scale * image->pixmap()->size());
    QScrollBar *horizontal = horizontalScrollBar();
    QScrollBar *vertical = verticalScrollBar();
    int hscroll = int(factor * horizontal->value() + ((factor - 1) * horizontal->pageStep() / 2));
    int vscroll = int(factor * vertical->value() + ((factor - 1) * vertical->pageStep() / 2));
    horizontal->setValue(hscroll);
    vertical->setValue(vscroll);
}

Viewer::~Viewer()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
