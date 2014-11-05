#include "partitions.hpp"

using namespace VPZ::APKStudio::Helpers;
using namespace VPZ::APKStudio::Resources;

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

void Partitions::onAction(QAction *action)
{
    switch (action->data().toInt())
    {
    case ACTION_REMOUNT:
        onRemount();
        break;
    case ACTION_UNMOUNT:
        onUnmount();
        break;
    }
}

void Partitions::onRefresh()
{
    if (model()->hasChildren())
        model()->removeRows(0, model()->rowCount());
    QVector<Partition> partitions = ADB::instance()->partitions(device);
    foreach (const Partition &partition, partitions) {
        QTreeWidgetItem *row = new QTreeWidgetItem();
        for (int i = 0; i < 5; ++i)
            row->setData(i, ROLE_STRUCT, QVariant::fromValue(partition));
        bool rw = partition.flags.contains("rw");
        row->setIcon(0, ::icon(rw ? "lock_unlock" : "lock_warning"));
        row->setText(0, partition.mount);
        row->setText(1, partition.device);
        row->setText(2, rw ? "Yes" : "No");
        row->setText(3, partition.fs);
        row->setText(4, partition.flags.join(", "));
        row->setToolTip(4, partition.flags.join(", "));
        addTopLevelItem(row);
    }
    scrollToTop();
}

void Partitions::onRemount()
{
    QVector<Partition> partitions = selected();
    if (partitions.count() != 1)
        return;
    Partition partition = partitions.first();
    if (ADB::instance()->remount(device, partition)) {
        if (partition.flags.contains("ro"))
            partition.flags.replace(partition.flags.indexOf("ro"), "rw");
        else if (partition.flags.contains("rw"))
            partition.flags.replace(partition.flags.indexOf("rw"), "ro");
        QList<QTreeWidgetItem *> rows = findItems(partition.mount, Qt::MatchExactly, 0);
        if (rows.count() != 1)
            onRefresh();
        bool rw = partition.flags.contains("rw");
        for (int i = 0; i < 5; ++i)
            rows.first()->setData(i, ROLE_STRUCT, QVariant::fromValue(partition));
        rows.first()->setIcon(0, ::icon(rw ? "lock_unlock" : "lock_warning"));
        rows.first()->setText(2, rw ? "Yes" : "No");
    } else
        QMessageBox::critical(this, translate("title_failure"), translate("message_remount_failed").arg(partition.mount), QMessageBox::Close);
}

void Partitions::onUnmount()
{
    QVector<Partition> partitions = selected();
    if (partitions.count() != 1)
        return;
    Partition partition = partitions.first();
    int result =  QMessageBox::question(this, translate("title_unmount"), translate("message_unmount").arg(partition.mount), QMessageBox::No | QMessageBox::Yes);
    if (result != QMessageBox::Yes)
        return;
    if (ADB::instance()->unmount(device, partition)) {
        QList<QTreeWidgetItem *> rows = findItems(partition.mount, Qt::MatchExactly, 0);
        if (rows.count() != 1)
            onRefresh();
        delete rows.first();
    } else
        QMessageBox::critical(this, translate("title_failure"), translate("message_unmount_failed").arg(partition.mount), QMessageBox::Close);
}

QVector<Partition> Partitions::selected()
{
    QVector<Partition> partitions;
    foreach (QTreeWidgetItem *item, selectedItems())
        partitions.append(item->data(0, ROLE_STRUCT).value<Partition>());
    return partitions;
}

Partitions::~Partitions()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
