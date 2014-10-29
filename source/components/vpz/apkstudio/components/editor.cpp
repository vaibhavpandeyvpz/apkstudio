#include "editor.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Editor::Editor(QWidget *parent) :
    QWidget(parent)
{
    QSizePolicy left(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy right(QSizePolicy::Preferred, QSizePolicy::Preferred);
    left.setHorizontalStretch(2);
    right.setHorizontalStretch(4);
    // -- //
    QVBoxLayout *layout = new QVBoxLayout(this);
    QToolBar *tool_bar = new QToolBar(this);
    files = new QComboBox(tool_bar);
    stack = new QStackedWidget(this);
    this->symbols = new QComboBox(tool_bar);
    this->variants = new QComboBox(tool_bar);
    files->setStyleSheet(STYLESHEET_COMBOBOXES);
    files->setSizePolicy(left);
    layout->addWidget(tool_bar);
    layout->addWidget(stack);
    layout->setContentsMargins(0, 1, 0, 2);
    layout->setSpacing(2);
    this->symbols->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->symbols->setStyleSheet(STYLESHEET_COMBOBOXES);
    this->symbols->setSizePolicy(right);
    tool_bar->addWidget(files);
    QAction *symbols = tool_bar->addWidget(this->symbols);
    tool_bar->layout()->setContentsMargins(0, 0, 0, 0);
    tool_bar->layout()->setSpacing(2);
    this->variants->setStyleSheet(STYLESHEET_COMBOBOXES);
    this->variants->setSizePolicy(right);
    QAction *variants = tool_bar->addWidget(this->variants);
    variants->setVisible(false);
    setLayout(layout);
    setMinimumSize(64, 64);
    connections.append(connect(files, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [ symbols, variants, this ] (int index) {
        this->stack->setCurrentIndex(index);
        emit selectionChanged(index);
        QWidget *widget = this->stack->currentWidget();
        if (!widget)
            return;
        if (widget->inherits(Viewer::staticMetaObject.className())) {
            symbols->setVisible(false);
            variants->setVisible(true);
        } else {
            symbols->setVisible(true);
            variants->setVisible(false);
        }
        widget->setFocus();
    }));
}

void Editor::first()
{
    int current = files->currentIndex();
    if (current != 0)
        files->setCurrentIndex(0);
}

void Editor::last()
{
    int current = files->currentIndex();
    int total = files->count();
    if (current < total)
        files->setCurrentIndex(total - 1);
}

void Editor::next()
{
    int current = files->currentIndex();
    if (current < files->count())
        files->setCurrentIndex(current + 1);
}

void Editor::open(const QString &path)
{
    QFileInfo info(path);
    if (!info.exists() || !info.isFile())
        return;
    QWidget *widget;
    if (QString(ALLOWED_IMAGE_EXTENSIONS).contains(info.suffix())) {
        Viewer *viewer = new Viewer(stack);
        viewer->open(info);
        widget = viewer;
    } else if (QString(ALLOWED_TEXT_EXTENSIONS).contains(info.suffix())) {
        Coder *coder = new Coder(stack);
        coder->open(info);
        widget = coder;
    } else
        return;
    files->addItem(info.fileName(), QVariant(info.absoluteFilePath()));
    files->setCurrentIndex(stack->addWidget(widget));
    widget->setFocus();
}

void Editor::onSelectionChanged(int index)
{
    this->files->setCurrentIndex(index);
}

void Editor::previous()
{
    int current = files->currentIndex();
    if (current > 0)
        files->setCurrentIndex(current - 1);
}

Editor::~Editor()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
