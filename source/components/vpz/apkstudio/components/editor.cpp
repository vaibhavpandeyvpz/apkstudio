#include "editor.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Editor::Editor(QStandardItemModel *model, QWidget *parent) :
    QWidget(parent), editables(Settings::fileIcons())
{
    QSizePolicy left(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy right(QSizePolicy::Preferred, QSizePolicy::Preferred);
    left.setHorizontalStretch(2);
    right.setHorizontalStretch(4);
    // -- //
    QVBoxLayout *layout = new QVBoxLayout(this);
    QToolBar *tool_bar = new QToolBar(this);
    files = new QComboBox(tool_bar);
    tabs = new QTabWidget(this);
    tabs->setTabsClosable(true);
    this->variants = new QComboBox(tool_bar);
    files->setModel(model);
    files->setStyleSheet(STYLESHEET_COMBOBOXES);
    files->setSizePolicy(left);
    layout->addWidget(tool_bar);
    layout->addWidget(tabs);
    layout->setContentsMargins(0, 1, 0, 2);
    layout->setSpacing(2);
    tool_bar->addWidget(files);
    tool_bar->layout()->setContentsMargins(0, 0, 0, 0);
    tool_bar->layout()->setSpacing(2);
    this->variants->setStyleSheet(STYLESHEET_COMBOBOXES);
    this->variants->setSizePolicy(right);
    QAction *variants = tool_bar->addWidget(this->variants);
    variants->setVisible(false);
    setLayout(layout);
    setMinimumSize(64, 64);
    connections.append(connect(tabs, static_cast<void(QTabWidget::*)(int)>(&QTabWidget::tabCloseRequested), [ this ] (int index) {
        this->files->removeItem(index);
        this->tabs->removeTab(index);
    }));
    connections.append(connect(tabs, static_cast<void(QTabWidget::*)(int)>(&QTabWidget::currentChanged), [ this ] (int index) {
        if (index < 0)
            return;
        this->files->setCurrentIndex(index);
    }));
    connections.append(connect(files, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [ variants, this ] (int index) {
        if (index < 0)
            return;
        this->tabs->setCurrentIndex(index);
        emit selectionChanged(index);
        QWidget *widget = this->tabs->currentWidget();
        if (!widget)
            return;
        if (widget->inherits(Viewer::staticMetaObject.className()))
            variants->setVisible(true);
        else
            variants->setVisible(false);
        widget->setFocus();
    }));
}

void Editor::close()
{
    int index = files->currentIndex();
    if (index < 0)
        return;
    files->removeItem(index);
    tabs->removeTab(index);
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
    int current = (files->currentIndex() + 1);
    if (current < files->count())
        files->setCurrentIndex(current);
}

void Editor::onSelectionChanged(int index)
{
    files->setCurrentIndex(index);
}

void Editor::open(const QFileInfo &info)
{
    if (!info.exists() || !info.isFile())
        return;
    int index = files->findData(info.absoluteFilePath());
    if (index >= 0) {
        files->setCurrentIndex(index);
        return;
    }
    QWidget *widget;
    if (QString(ALLOWED_IMAGE_EXTENSIONS).contains(info.suffix())) {
        Viewer *viewer = new Viewer(tabs);
        viewer->open(info);
        widget = viewer;
    } else if (QString(ALLOWED_TEXT_EXTENSIONS).contains(info.suffix())) {
        Coder *coder = new Coder(tabs);
        coder->open(info);
        widget = coder;
    } else
        return;
    QIcon icon = (editables.contains(info.suffix()) ? ::icon(info.suffix()) : ::icon("file"));
    index = tabs->addTab(widget, icon, info.fileName());
    files->addItem(icon, info.fileName(), info.absoluteFilePath());
    files->setCurrentIndex(index);
    tabs->setTabToolTip(index, info.absoluteFilePath());
    widget->setFocus();
    widget->setProperty("path", info.absoluteFilePath());
}

void Editor::previous()
{
    int current = files->currentIndex();
    if (current > 0)
        files->setCurrentIndex(current - 1);
}

void Editor::save(const bool all)
{
    int index = all ? 0 : files->currentIndex();
    if (index < 0)
        return;
    do {
        Coder *coder = qobject_cast<Coder *>(tabs->widget(index));
        if (coder != nullptr)
            coder->save();
        else {
            Viewer *viewer = qobject_cast<Viewer *>(tabs->widget(index));
            if (viewer != nullptr)
                viewer->save();
        }
        index++;
    } while (all && (index < files->count()));
}

Editor::~Editor()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
