#include "applications.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Applications::Applications(const QString &device, QWidget *parent) :
    QTreeWidget(parent), device(device)
{
    QStringList labels;
    labels << translate("header_file");
    labels << translate("header_package");
    labels << translate("header_system");
    labels << translate("header_status");
    setHeaderLabels(labels);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setRootIsDecorated(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSortingEnabled(true);
    sortByColumn(0, Qt::AscendingOrder);
}

Applications::~Applications()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

void Applications::onInitComplete()
{
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
