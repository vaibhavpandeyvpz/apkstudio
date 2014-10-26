#include "devicechooser.hpp"
#include <QDebug>

using namespace VPZ::APKStudio::Helpers;
using namespace VPZ::APKStudio::Resources;

namespace VPZ {
namespace APKStudio {
namespace Components {

DeviceChooser::DeviceChooser(QWidget *parent) :
    QWidget(parent)
{
    QToolBar *toolbar = new QToolBar(this);
    QToolButton *adb = new QToolButton(this);
    QAction *browse = new QAction(icon("folder_stand"), translate("item_browse"), toolbar);
    QAction *information = new QAction(icon("processor"), translate("item_information"), toolbar);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QAction *kill = new QAction(icon("control_stop"), translate("item_kill"), toolbar);
    QAction *logcat = new QAction(icon("resource_monitor"), translate("item_logcat"), toolbar);
    QMenu *menu = new QMenu(adb);
    QAction *refresh = new QAction(icon("arrow_circle_double"), translate("item_refresh"), toolbar);
    QAction *restart = new QAction(icon("arrow_circle"), translate("item_restart"), toolbar);
    QAction *screenshot = new QAction(icon("camera"), translate("item_screenshot"), toolbar);
    QAction *shell = new QAction(icon("terminal"), translate("item_shell"), toolbar);
    QAction *start = new QAction(icon("control_play"), translate("item_start"), toolbar);
    tree = new QTreeView(this);
    model = new QStandardItemModel(tree);
    adb->setDefaultAction(restart);
    adb->setIcon(icon("control_power"));
    adb->setText(translate("item_adb"));
    adb->setToolTip(translate("tooltip_adb"));
    adb->setMenu(menu);
    adb->setPopupMode(QToolButton::MenuButtonPopup);
    browse->setEnabled(false);
    information->setEnabled(false);
    layout->addWidget(toolbar);
    layout->addWidget(tree);
    layout->setContentsMargins(QMargins(2, 2, 2, 2));
    layout->setSpacing(0);
    logcat->setEnabled(false);
    menu->addAction(start);
    menu->addAction(kill);
    menu->addSeparator();
    menu->addAction(restart);
    model->setHorizontalHeaderItem(0, new QStandardItem(""));
    model->setHorizontalHeaderItem(1, new QStandardItem(translate("header_serial")));
    model->setHorizontalHeaderItem(2, new QStandardItem(translate("header_type")));
    screenshot->setEnabled(false);
    shell->setEnabled(false);
    toolbar->addWidget(adb);
    toolbar->addAction(refresh);
    toolbar->addSeparator();
    toolbar->addAction(information);
    toolbar->addSeparator();
    toolbar->addAction(browse);
    toolbar->addAction(screenshot);
    toolbar->addAction(logcat);
    toolbar->addAction(shell);
    tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tree->setRootIsDecorated(false);
    tree->setModel(model);
    tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    tree->setSelectionMode(QAbstractItemView::SingleSelection);
    tree->setSortingEnabled(true);
    tree->sortByColumn(1, Qt::AscendingOrder);
    connect(browse, SIGNAL(triggered()), this, SLOT(onBrowse()));
    connect(information, SIGNAL(triggered()), this, SLOT(onInformation()));
    connections.append(connect(kill, &QAction::triggered, [] () {
        ADB::instance()->kill();
    }));
    connect(logcat, SIGNAL(triggered()), this, SLOT(onLogcat()));
    connect(refresh, SIGNAL(triggered()), this, SLOT(onRefresh()));
    connections.append(connect(restart, &QAction::triggered, [] () {
        ADB::instance()->kill();
        ADB::instance()->start();
    }));
    connect(screenshot, SIGNAL(triggered()), this, SLOT(onScreenshot()));
    connect(shell, SIGNAL(triggered()), this, SLOT(onShell()));
    connections.append(connect(start, &QAction::triggered, [] () {
        ADB::instance()->start();
    }));
    connections.append(connect(tree->selectionModel(), &QItemSelectionModel::selectionChanged, [ browse, information, logcat, screenshot, shell, this ] (const QItemSelection &/*current*/, const QItemSelection &/*previous*/) {
        bool enable = false;
        Device device = this->selected();
        if (!device.serial.isEmpty())
            enable = (device.status == Device::ONLINE);
        browse->setEnabled(enable);
        information->setEnabled(enable);
        logcat->setEnabled(enable);
        screenshot->setEnabled(enable);
        shell->setEnabled(enable);
    }));
    setLayout(layout);
    setMinimumSize(160, 160);
}

void DeviceChooser::onBrowse()
{

}

void DeviceChooser::onInformation()
{

}

void DeviceChooser::onLogcat()
{

}

void DeviceChooser::onRefresh()
{
    QVector<Device> devices = ADB::instance()->devices();
    if (devices.count() <= 0)
        return;
    while (model->rowCount() > 0)
        model->removeRow(0);
    foreach (const Device &device, devices) {
        QStandardItem *icon = new QStandardItem();
        QStandardItem *serial = new QStandardItem(device.serial);
        QStandardItem *type = new QStandardItem();
        switch (device.status) {
        case Device::BOOTLOADER:
            icon->setIcon(this->icon("mobile_phone_warning"));
            icon->setToolTip(translate("status_bootloader"));
            break;
        case Device::ONLINE:
            icon->setIcon(this->icon("mobile_phone"));
            icon->setToolTip(translate("status_online"));
            break;
        default:
            icon->setIcon(this->icon("mobile_phone_off"));
            icon->setToolTip(translate("status_offline"));
            break;
        }
        switch (device.type) {
        case Device::DEVICE:
            type->setText(translate("type_phone"));
            break;
        default:
            type->setText(translate("type_emulator"));
            break;
        }
        QVariant data;
        data.setValue(device);
        icon->setData(data, ROLE_STRUCT);
        QList<QStandardItem *> row;
        row << icon;
        row << serial;
        row << type;
        model->appendRow(row);
    }
    tree->header()->resizeSections(QHeaderView::ResizeToContents);
}

void DeviceChooser::onScreenshot()
{
    Device device = selected();
    if ((device.serial.isEmpty()) || (device.status != Device::ONLINE))
        return;
    QString file = QString(Settings::previousDirectory());
    file.append(device.serial);
    file.append('_');
    file.append(Format::timestamp(QDateTime::currentDateTime(), FORMAT_TIMESTAMP_FILE));
    QString path = QFileDialog::getSaveFileName(this, translate("title_save"), file, QString("PNG Image Files (*.png)"));
    if (path.isNull() || path.isEmpty())
        return;
    if (QFile::exists(path))
        QFile::remove(path);
    Settings::previousDirectory(QFileInfo(path).dir().absolutePath());
    ADB::instance()->screenshot(device.serial, path);
    if (QFile::exists(path))
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void DeviceChooser::onShell()
{
    Device device = selected();
    if ((device.serial.isEmpty()) || (device.status != Device::ONLINE))
        return;
    ADB::instance()->shell(device.serial);
}

Device DeviceChooser::selected() const
{
    Device device;
    QModelIndexList selection = this->tree->selectionModel()->selectedRows(0);
    if (selection.count() == 1)
        device = qvariant_cast<Device>(selection.first().data(ROLE_STRUCT));
    return device;
}

DeviceChooser::~DeviceChooser()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
