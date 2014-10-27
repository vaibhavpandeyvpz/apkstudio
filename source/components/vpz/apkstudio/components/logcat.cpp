#include "logcat.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Logcat::Logcat(QWidget *parent) :
    QWidget(parent)
{
    QToolBar *tool_bar = new QToolBar(this);
    QAction *clear = new QAction(icon("bin_empty"), translate("label_clear"), tool_bar);
    QAction *debug = new QAction(icon("info_debug"), translate("label_debug"), tool_bar);
    QAction *error = new QAction(icon("info_error"), translate("label_error"), tool_bar);
    QAction *info = new QAction(icon("info_success"), translate("label_info"), tool_bar);
    QAction *open = new QAction(icon("folder_open"), translate("label_open"), tool_bar);
    QAction *save = new QAction(icon("disk"), translate("label_save"), tool_bar);
    QAction *scroll = new QAction(icon("arrow_skip_bottom"), translate("label_scroll"), tool_bar);
    QAction *start = new QAction(icon("control_play"), translate("label_start"), tool_bar);
    QAction *stop = new QAction(icon("control_stop"), translate("label_stop"), tool_bar);
    QAction *verbose = new QAction(icon("info_verbose"), translate("label_verbose"), tool_bar);
    QAction *warning = new QAction(icon("info_warning"), translate("label_warning"), tool_bar);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QList<QAction *> control;
    control << start;
    control << stop;
    QList<QAction *> level;
    level << verbose;
    level << debug;
    level << info;
    level << warning;
    level << error;
    tree = new QTreeWidget(this);
    debug->setCheckable(true);
    debug->setChecked(true);
    error->setCheckable(true);
    error->setChecked(true);
    info->setCheckable(true);
    info->setChecked(true);
    layout->addWidget(tool_bar);
    layout->addWidget(tree);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    scroll->setCheckable(true);
    scroll->setChecked(true);
    stop->setEnabled(false);
    verbose->setCheckable(true);
    verbose->setChecked(true);
    warning->setCheckable(true);
    warning->setChecked(true);
    tool_bar->setAcceptDrops(false);
    tool_bar->setMovable(false);
    tool_bar->addActions(control);
    tool_bar->addSeparator();
    tool_bar->addAction(open);
    tool_bar->addAction(clear);
    tool_bar->addSeparator();
    tool_bar->addActions(level);
    tool_bar->addSeparator();
    tool_bar->addAction(save);
    tool_bar->addSeparator();
    tool_bar->addAction(scroll);
    tree->setContextMenuPolicy(Qt::CustomContextMenu);
    tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tree->setRootIsDecorated(false);
    tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    tree->setSelectionMode(QAbstractItemView::MultiSelection);
    tree->setSortingEnabled(true);
    tree->setUniformRowHeights(true);
    tree->sortByColumn(1, Qt::DescendingOrder);
    QStringList labels;
    labels << translate("header_priority");
    labels << translate("header_time");
    labels << translate("header_pid");
    labels << translate("header_tid");
    labels << translate("header_tag");
    labels << translate("header_message");
    tree->setHeaderLabels(labels);
    tree->setColumnWidth(0, 64);
    tree->setColumnWidth(1, 128);
    tree->setColumnWidth(2, 48);
    tree->setColumnWidth(3, 48);
    tree->setColumnWidth(4, 128);
    connections.append(connect(clear, &QAction::triggered, [ this ] () {
        if (this->tree->model()->hasChildren())
            this->tree->model()->removeRows(0, this->tree->model()->rowCount());
    }));
    connections.append(connect(scroll, &QAction::toggled, [ this ] (bool checked) {
        this->scroll = checked;
    }));
    setMinimumSize(160, 160);
}

void Logcat::setDevice(const QString &serial)
{
}

Logcat::~Logcat()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
