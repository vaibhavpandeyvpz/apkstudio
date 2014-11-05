#include "treewidget.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

TreeWidget::TreeWidget(const bool drag, const bool drop, QWidget *parent) :
    QTreeWidget(parent)
{
    if (drop) {
        setAcceptDrops(true);
        setDragDropMode(QAbstractItemView::InternalMove);
    }
    if (!drag)
        return;
    setDragEnabled(true);
}

void TreeWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void TreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

void TreeWidget::dropEvent(QDropEvent *event)
{
    QModelIndex target = indexAt(event->pos());
    QStringList files;
    QList<QUrl> urls = event->mimeData()->urls();
    foreach(const QUrl &url, urls)
        files << url.toLocalFile();
    if (!files.empty()) {
        emit filesDropped(files, target);
        return;
    }
    if (!event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
        return;
    QModelIndexList indexes;
    QList<QTreeWidgetItem *> dragged = selectedItems();
    foreach (QTreeWidgetItem *item, dragged)
        indexes << indexFromItem(item);
    emit itemsDropped(indexes, target, event->dropAction());
}

QModelIndex TreeWidget::index(QTreeWidgetItem *item, int column)
{
    return indexFromItem(item, column);
}

QTreeWidgetItem *TreeWidget::item(const QModelIndex &index)
{
    return itemFromIndex(index);
}

TreeWidget::~TreeWidget()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
