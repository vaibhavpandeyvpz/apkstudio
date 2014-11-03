#include "partitions.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Partitions::Partitions(const QString &device, QWidget *parent) :
    QTreeWidget(parent), device(device)
{
    QStringList labels;
    labels << translate("header_partition");
    labels << translate("header_device");
    labels << translate("header_rw");
    labels << translate("header_fs");
    labels << translate("header_flags");
    setHeaderLabels(labels);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setRootIsDecorated(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSortingEnabled(true);
    sortByColumn(3, Qt::DescendingOrder);
}

void Partitions::onInitComplete()
{
}

Partitions::~Partitions()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
