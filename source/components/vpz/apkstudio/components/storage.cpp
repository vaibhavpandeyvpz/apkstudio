#include "storage.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Storage::Storage(const QString &device, QWidget *parent) :
    QTreeWidget(parent), device(device)
{
    QStringList labels;
    labels << translate("header_name");
    labels << translate("header_size");
    labels << translate("header_permissions");
    labels << translate("header_owner");
    labels << translate("header_group");
    labels << translate("header_modified");
    setHeaderLabels(labels);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setRootIsDecorated(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSortingEnabled(true);
    sortByColumn(5, Qt::DescendingOrder);
}

void Storage::onInitComplete()
{
}

Storage::~Storage()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
