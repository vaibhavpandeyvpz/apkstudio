#include "music.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Music::Music(const QString &device, QWidget *parent) :
    QTreeWidget(parent), device(device)
{
    QStringList labels;
    labels << translate("header_name");
    labels << translate("header_duration");
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

void Music::onAction(QAction *action)
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

void Music::onCopy()
{
}

void Music::onDetails()
{
}

void Music::onMove()
{
}

void Music::onPull()
{
}

void Music::onRefresh()
{
    if (model()->hasChildren())
        model()->removeRows(0, model()->rowCount());
    QVector<Resources::Music> musics = ADB::instance()->music(device);
    foreach (const Resources::Music &music, musics) {
        QTreeWidgetItem *row = new QTreeWidgetItem();
        for (int i = 0; i < 4; ++i)
            row->setData(i, ROLE_STRUCT, QVariant::fromValue(music));
        row->setIcon(0, ::icon("music"));
        row->setText(0, music.name);
        row->setText(1, Format::timestamp(QDateTime::fromTime_t(music.duration / 1000).toUTC(), "hh:mm:ss"));
        row->setText(2, Format::size(music.size));
        row->setText(3, Format::timestamp(QDateTime::fromTime_t(music.time)));
        row->setToolTip(0, music.path);
        addTopLevelItem(row);
    }
    scrollToTop();
}

void Music::onRemove()
{
}

void Music::onRename()
{
}

Music::~Music()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
