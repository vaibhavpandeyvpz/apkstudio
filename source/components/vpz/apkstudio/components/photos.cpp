#include "photos.hpp"

using namespace VPZ::APKStudio::Helpers;
using namespace VPZ::APKStudio::Resources;

namespace VPZ {
namespace APKStudio {
namespace Components {

Photos::Photos(const QString &device, QWidget *parent) :
    QTreeWidget(parent), device(device)
{
    QStringList labels;
    labels << translate("header_name");
    labels << translate("header_resolution");
    labels << translate("header_size");
    labels << translate("header_time");
    setHeaderLabels(labels);
    setColumnWidth(0, 160);
    setColumnWidth(1, 64);
    setColumnWidth(2, 64);
    setColumnWidth(3, 96);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setRootIsDecorated(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSortingEnabled(true);
    sortByColumn(3, Qt::DescendingOrder);
}

void Photos::onAction(QAction *action)
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

void Photos::onCopy()
{
}

void Photos::onDetails()
{
}

void Photos::onMove()
{
}

void Photos::onPull()
{
}

void Photos::onRefresh()
{
    if (model()->hasChildren())
        model()->removeRows(0, model()->rowCount());
    QVector<Photo> photos = ADB::instance()->photos(device);
    foreach (const Photo &photo, photos) {
        QTreeWidgetItem *row = new QTreeWidgetItem();
        for (int i = 0; i < 4; ++i)
            row->setData(i, ROLE_STRUCT, QVariant::fromValue(photo));
        row->setIcon(0, ::icon("image"));
        row->setText(0, photo.name);
        row->setText(1, QString::number(photo.width).append('x').append(QString::number(photo.height)));
        row->setText(2, Format::size(photo.size));
        row->setText(3, Format::timestamp(QDateTime::fromTime_t(photo.time)));
        row->setToolTip(0, photo.path);
        addTopLevelItem(row);
    }
    scrollToTop();
}

void Photos::onRemove()
{
}

void Photos::onRename()
{
}

Photos::~Photos()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
