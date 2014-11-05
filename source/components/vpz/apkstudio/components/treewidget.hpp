#ifndef VPZ_APKSTUDIO_COMPONENTS_TREEWIDGET_HPP
#define VPZ_APKSTUDIO_COMPONENTS_TREEWIDGET_HPP

#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QTreeWidget>

namespace VPZ {
namespace APKStudio {
namespace Components {

class TreeWidget : public QTreeWidget
{
    Q_OBJECT
protected:
    QList<QMetaObject::Connection> connections;
protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);
public:
    explicit TreeWidget(const bool = false, const bool = false, QWidget * = 0);
    QModelIndex index(QTreeWidgetItem *, int = 0);
    QTreeWidgetItem *item(const QModelIndex &);
    ~TreeWidget();
signals:
    void filesDropped(QStringList, QModelIndex);
    void itemsDropped(QModelIndexList, QModelIndex, Qt::DropAction);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_TREEWIDGET_HPP
