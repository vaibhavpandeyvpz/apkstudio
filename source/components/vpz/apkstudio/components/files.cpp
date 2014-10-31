#include "files.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Files::Files(QStandardItemModel *model, QWidget *parent) :
    Dockable(translate("title_dock"), parent)
{
    list = new QListView(this);
    list->setContextMenuPolicy(Qt::CustomContextMenu);
    list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    list->setSelectionBehavior(QAbstractItemView::SelectRows);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    list->setMinimumSize(64, 64);
    list->setModel(model);
    connections.append(connect(list->selectionModel(), &QItemSelectionModel::selectionChanged, [ this ] (QItemSelection, QItemSelection) {
        QModelIndexList selection = this->list->selectionModel()->selectedRows(0);
        if (selection.count() != 1)
            return;
        emit selectionChanged(selection.first().row());
    }));
    setObjectName("files");
    setWidget(list);
}

void Files::onSelectionChanged(int row)
{
    QModelIndex index = list->model()->index(row, 0);
    if (index.isValid())
        list->setCurrentIndex(index);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
