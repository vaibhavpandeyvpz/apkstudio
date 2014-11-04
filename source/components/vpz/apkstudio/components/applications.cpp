#include "applications.hpp"

using namespace VPZ::APKStudio::Helpers;
using namespace VPZ::APKStudio::Resources;

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
    setColumnWidth(0, 160);
    setColumnWidth(1, 160);
    setColumnWidth(2, 64);
    setColumnWidth(3, 64);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setRootIsDecorated(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::MultiSelection);
    setSortingEnabled(true);
    sortByColumn(0, Qt::AscendingOrder);
}

void Applications::onAction(QAction *action)
{
    switch (action->data().toInt())
    {
    case ACTION_DETAILS:
        onDetails();
        break;
    case ACTION_DISABLE:
        onDisable();
        break;
    case ACTION_ENABLE:
        onEnable();
        break;
    case ACTION_INSTALL:
        onInstall();
        break;
    case ACTION_PULL:
        onPull();
        break;
    case ACTION_UNINSTALL:
        onUninstall();
        break;
    }
}

void Applications::onDetails()
{
}

void Applications::onDisable()
{
}

void Applications::onEnable()
{
}

void Applications::onInitComplete()
{
    onRefresh();
}

void Applications::onInstall()
{
}

void Applications::onPull()
{
}

void Applications::onUninstall()
{
}

void Applications::onRefresh()
{
    if (model()->hasChildren())
        model()->removeRows(0, model()->rowCount());
    QVector<Application> applications = ADB::instance()->applications(device);
    foreach (const Application &application, applications) {
        QTreeWidgetItem *row = new QTreeWidgetItem();
        for (int i = 0; i < 4; ++i)
            row->setData(i, ROLE_STRUCT, QVariant::fromValue(application));
        row->setIcon(0, ::icon(application.enabled ? "tick" : "cross"));
        row->setText(0, application.name);
        row->setText(1, application.package);
        row->setText(2, application.system ? "Yes" : "No");
        row->setText(3, application.enabled ? "Enabled" : "Disabled");
        row->setToolTip(0, application.path);
        addTopLevelItem(row);
    }
    scrollToTop();
}

Applications::~Applications()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
