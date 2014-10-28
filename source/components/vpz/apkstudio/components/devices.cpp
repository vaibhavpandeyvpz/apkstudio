#include "devices.hpp"

using namespace VPZ::APKStudio::Helpers;
using namespace VPZ::APKStudio::Resources;

namespace VPZ {
namespace APKStudio {
namespace Components {

Devices::Devices(QWidget *parent) :
    QDockWidget(translate("title_dock"), parent)
{
    QWidget *widget = new QWidget(this);
    QToolBar *toolbar = new QToolBar(widget);
    QToolButton *adb = new QToolButton(widget);
    QAction *browse = new QAction(icon("folder_stand"), translate("item_browse"), toolbar);
    QAction *information = new QAction(icon("processor"), translate("item_information"), toolbar);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    QAction *kill = new QAction(icon("control_stop"), translate("item_kill"), toolbar);
    QAction *logcat = new QAction(icon("resource_monitor"), translate("item_logcat"), toolbar);
    QMenu *menu = new QMenu(adb);
    QAction *refresh = new QAction(icon("arrow_circle_double"), translate("item_refresh"), toolbar);
    QAction *restart = new QAction(icon("arrow_circle"), translate("item_restart"), toolbar);
    QAction *screenshot = new QAction(icon("camera"), translate("item_screenshot"), toolbar);
    QAction *shell = new QAction(icon("terminal"), translate("item_shell"), toolbar);
    QAction *start = new QAction(icon("control_play"), translate("item_start"), toolbar);
    tree = new QTreeWidget(widget);
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
    layout->setContentsMargins(QMargins(0, 0, 0, 0));
    layout->setSpacing(0);
    logcat->setEnabled(false);
    menu->addAction(start);
    menu->addAction(kill);
    menu->addSeparator();
    menu->addAction(restart);
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
    QStringList labels;
    labels << "";
    labels << translate("header_serial");
    labels << translate("header_type");
    tree->setHeaderLabels(labels);
    tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tree->setRootIsDecorated(false);
    tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    tree->setSelectionMode(QAbstractItemView::SingleSelection);
    tree->setColumnWidth(0, 32);
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
    widget->setLayout(layout);
    widget->setMinimumSize(64, 64);
    setContentsMargins(2, 2, 2, 2);
    setObjectName("devices");
    setWidget(widget);
}

void Devices::onBrowse()
{

}

void Devices::onInformation()
{
    Device device = selected();
    if ((device.serial.isEmpty()) || (device.status != Device::ONLINE))
        return;
    Dialog *dialog = new Dialog(this);
    Information *information = new Information(dialog);
    QHBoxLayout *layout = new QHBoxLayout(dialog);
    layout->addWidget(information);
    layout->setContentsMargins(QMargins(2, 2, 2, 2));
    layout->setSpacing(0);
    dialog->setDialogLayout(layout);
    dialog->resize(QSize(360, 256));
    dialog->setMinimumSize(QSize(320, 240));
    dialog->setMaximumSize(QSize(800, 600));
#ifdef Q_OS_WIN
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
    dialog->setWindowIcon(icon("processor"));
    dialog->setWindowTitle(translate("title_information").arg(device.serial));
    dialog->show();
    information->setDevice(device.serial);
}

void Devices::onLogcat()
{
    Device device = selected();
    if ((device.serial.isEmpty()) || (device.status != Device::ONLINE))
        return;
    Dialog *dialog = new Dialog(this);
    Logcat *logcat = new Logcat(dialog);
    QHBoxLayout *layout = new QHBoxLayout(dialog);
    layout->addWidget(logcat);
    layout->setContentsMargins(QMargins(0, 0, 0, 0));
    layout->setSpacing(0);
    dialog->setDialogLayout(layout);
    dialog->resize(QSize(480, 320));
    dialog->setMinimumSize(QSize(320, 240));
    dialog->setMaximumSize(QSize(800, 600));
#ifdef Q_OS_WIN
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
    dialog->setWindowIcon(icon("resource_monitor"));
    dialog->setWindowTitle(translate("title_logcat").arg(device.serial));
    dialog->show();
    logcat->setDevice(device.serial);
}

void Devices::onRefresh()
{
    QVector<Device> devices = ADB::instance()->devices();
    if (devices.count() <= 0)
        return;
    if (tree->model()->hasChildren())
        tree->model()->removeRows(0, tree->model()->rowCount());
    foreach (const Device &device, devices) {
        QTreeWidgetItem *row = new QTreeWidgetItem();
        switch (device.status) {
        case Device::BOOTLOADER:
            row->setIcon(0, this->icon("mobile_phone_warning"));
            row->setToolTip(0, translate("status_bootloader"));
            break;
        case Device::ONLINE:
            row->setIcon(0, this->icon("mobile_phone"));
            row->setToolTip(0, translate("status_online"));
            break;
        default:
            row->setIcon(0, this->icon("mobile_phone_off"));
            row->setToolTip(0, translate("status_offline"));
            break;
        }
        row->setText(1, device.serial);
        switch (device.type) {
        case Device::DEVICE:
            row->setText(2, translate("type_phone"));
            break;
        default:
            row->setText(2, translate("type_emulator"));
            break;
        }
        QVariant data;
        data.setValue(device);
        row->setData(0, ROLE_STRUCT, data);
        tree->addTopLevelItem(row);
    }
    tree->header()->resizeSections(QHeaderView::ResizeToContents);
}

void Devices::onScreenshot()
{
    Device device = selected();
    if ((device.serial.isEmpty()) || (device.status != Device::ONLINE))
        return;
    QString file = QString(Settings::previousDirectory());
    file.append('/');
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

void Devices::onShell()
{
    Device device = selected();
    if ((device.serial.isEmpty()) || (device.status != Device::ONLINE))
        return;
    ADB::instance()->shell(device.serial);
}

Device Devices::selected() const
{
    Device device;
    QModelIndexList selection = this->tree->selectionModel()->selectedRows(0);
    if (selection.count() == 1)
        device = qvariant_cast<Device>(selection.first().data(ROLE_STRUCT));
    return device;
}

Devices::~Devices()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
