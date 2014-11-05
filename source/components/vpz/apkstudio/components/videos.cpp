#include "videos.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Videos::Videos(const QString &device, QWidget *parent) :
    QTreeWidget(parent), device(device)
{
    QStringList labels;
    labels << translate("header_name");
    labels << translate("header_resolution");
    labels << translate("header_duration");
    labels << translate("header_size");
    labels << translate("header_time");
    setHeaderLabels(labels);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setRootIsDecorated(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSortingEnabled(true);
    sortByColumn(3, Qt::DescendingOrder);
}

void Videos::onAction(QAction *action)
{
    switch (action->data().toInt())
    {
    case ACTION_COPY:
        onCopy();
        break;
    case ACTION_DETAILS:
        onDetails();
        break;
    case ACTION_MOVE:
        onMove();
        break;
    case ACTION_PULL:
        onPull();
        break;
    case ACTION_REMOVE:
        onRemove();
        break;
    case ACTION_RENAME:
        onRename();
        break;
    }
}

void Videos::onCopy()
{
}

void Videos::onDetails()
{
}

void Videos::onMove()
{
}

void Videos::onPull()
{
}

void Videos::onRefresh()
{
}

void Videos::onRemove()
{
}

void Videos::onRename()
{
}

Videos::~Videos()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
