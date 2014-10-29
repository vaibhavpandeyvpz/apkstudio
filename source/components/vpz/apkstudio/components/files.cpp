#include "files.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Files::Files(QWidget *parent) :
    QDockWidget(translate("title_dock"), parent)
{
    list = new QListView(this);
    list->setContextMenuPolicy(Qt::CustomContextMenu);
    list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    list->setSelectionBehavior(QAbstractItemView::SelectRows);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    list->setMinimumSize(64, 64);
    setContentsMargins(2, 2, 2, 2);
    setObjectName("files");
    setWidget(list);
}

void Files::onSelectionChanged(int row)
{
    QModelIndex index = list->model()->index(row, 0);
    if (index.isValid())
        list->setCurrentIndex(index);
}

void Files::setModel(QAbstractItemModel *model)
{
    list->setModel(model);
    connections.append(connect(list->selectionModel(), &QItemSelectionModel::selectionChanged, [ this ] (const QItemSelection &/*current*/, const QItemSelection &/*previous*/) {
        QModelIndexList selection = this->list->selectionModel()->selectedRows(0);
        if (selection.count() != 1)
            return;
        emit selectionChanged(selection.first().row());
    }));
}

Files::~Files()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
