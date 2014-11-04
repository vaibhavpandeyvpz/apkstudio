#include "storage.hpp"

using namespace VPZ::APKStudio::Helpers;
using namespace VPZ::APKStudio::Resources;

namespace VPZ {
namespace APKStudio {
namespace Components {

Storage::Storage(const QString &device, QWidget *parent) :
    QTreeWidget(parent), device(device)
{
    path = new Clearable(this);
    tree = new QTreeWidget(this);
    QLayout *layout = new QVBoxLayout(this);
    QStringList labels;
    labels << translate("header_name");
    labels << translate("header_size");
    labels << translate("header_permissions");
    labels << translate("header_owner");
    labels << translate("header_group");
    labels << translate("header_modified");
    layout->addWidget(path);
    layout->addWidget(tree);
    layout->setContentsMargins(2, 2, 2, 2);
    layout->setSpacing(2);
    connections.append(connect(path, &Clearable::returnPressed, this, &Storage::onRefresh));
    connections.append(connect(tree, &QTreeWidget::doubleClicked, this, &Storage::onDoubleClicked));
    tree->setHeaderLabels(labels);
    tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tree->setRootIsDecorated(false);
    tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    tree->setSelectionMode(QAbstractItemView::MultiSelection);
    tree->setSortingEnabled(false);
    tree->setUniformRowHeights(true);
    tree->setColumnWidth(0, 160);
    tree->setColumnWidth(1, 96);
    tree->setColumnWidth(2, 96);
    tree->setColumnWidth(3, 96);
    tree->setColumnWidth(4, 96);
    tree->setColumnWidth(5, 128);
    setLayout(layout);
}

void Storage::onDoubleClicked(const QModelIndex &index)
{
    File file = index.data(ROLE_STRUCT).value<File>();
    switch (file.type) {
    case File::FOLDER:
    case File::SYMLINK_FOLDER: {
        path->setText(file.path);
        onRefresh();
        break;
    }
    default:
        break;
    }
}

void Storage::onAction(QAction *action)
{
    switch (action->data().toInt())
    {
    case ACTION_CHMOD:
        onCHMOD();
        break;
    case ACTION_COPY:
        onCopy();
        break;
    case ACTION_CREATE:
        onCreate();
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
    case ACTION_PUSH:
        onPush();
        break;
    case ACTION_REMOVE:
        onRemove();
        break;
    case ACTION_RENAME:
        onRename();
        break;
    }
}

void Storage::onCHMOD()
{
}

void Storage::onCopy()
{
}

void Storage::onCreate()
{
}

void Storage::onDetails()
{
}

void Storage::onInitComplete()
{
    onRefresh();
}

void Storage::onMove()
{
}

void Storage::onPull()
{
}

void Storage::onPush()
{
}

void Storage::onRefresh()
{
    int files = 0;
    int folders = 0;
    QString location(path->text());
    if (!location.startsWith('/')) {
        location.prepend('/');
        path->setText(location);
    }
    QString previous('/');
    if (location.count('/') > 1) {
        if (location.endsWith('/'))
            location = location.left(location.length() - 1);
        previous.append(location.mid(1, location.lastIndexOf('/')));
    }
    if (tree->model()->hasChildren())
        tree->model()->removeRows(0, tree->model()->rowCount());
    File file;
    file.type = File::FOLDER;
    file.path = previous;
    QTreeWidgetItem *up = new QTreeWidgetItem();
    for (int i = 0; i < 6; ++i)
        up->setData(i, ROLE_STRUCT, QVariant::fromValue(file));
    up->setIcon(0, ::icon("folder_previous"));
    up->setFlags(up->flags() & ~Qt::ItemIsSelectable);
    up->setText(0, "..");
    up->setToolTip(0, file.path);
    tree->addTopLevelItem(up);
    tree->setFirstColumnSpanned(0, tree->rootIndex(), true);
    QVector<File> list = ADB::instance()->files(device, location);
    foreach (file, list) {
        QTreeWidgetItem *row = new QTreeWidgetItem();
        switch (file.type) {
        case File::FOLDER:
        case File::SYMLINK_FOLDER:
            folders++;
            break;
        default:
            files++;
            break;
        }
        switch (file.type) {
        case File::BLOCK:
            row->setIcon(0, ::icon("file_block"));
            break;
        case File::CHARACTER:
            row->setIcon(0, ::icon("file_character"));
            break;
        case File::FOLDER:
            row->setIcon(0, ::icon("folder"));
            break;
        case File::FILE:
            row->setIcon(0, ::icon("file"));
            break;
        case File::PIPE:
            row->setIcon(0, ::icon("file_pipe"));
            break;
        case File::SOCKET:
            row->setIcon(0, ::icon("file_socket"));
            break;
        case File::SYMLINK_FOLDER:
            row->setIcon(0, ::icon("folder_symlink"));
            break;
        case File::SYMLINK_FILE:
            row->setIcon(0, ::icon("file_symlink"));
            break;
        case File::OTHER:
        case File::SYMLINK:
        default:
            row->setIcon(0, ::icon("file_unknown"));
            break;
        }
        for (int i = 0; i < 6; ++i)
            row->setData(i, ROLE_STRUCT, QVariant::fromValue(file));
        row->setText(0, file.name);
        row->setText(1, Format::size(file.size));
        row->setText(2, file.permission.display);
        row->setText(3, file.owner);
        row->setText(4, file.group);
        row->setText(5, QString(file.date).append(' ').append(file.time));
        row->setToolTip(0, file.path);
        tree->addTopLevelItem(row);
    }
    tree->scrollToTop();
}

void Storage::onRemove()
{
}

void Storage::onRename()
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
