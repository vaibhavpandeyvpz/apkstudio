#include <QAbstractItemView>
#include <QDebug>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QIcon>
#include <QMessageBox>
#include <QProgressDialog>
#include <QPushButton>
#include <QThread>
#include <QVBoxLayout>
#include "deviceselectiondialog.h"
#include "devicelistworker.h"

DeviceSelectionDialog::DeviceSelectionDialog(QWidget *parent)
    : QDialog(parent), m_ProgressDialog(nullptr)
{
    setWindowTitle(tr("Select device"));
    setMinimumSize(480, 240);
    resize(480, 240);
#ifdef Q_OS_WIN
    setWindowIcon(QIcon(":/icons/fugue/android.png"));
#endif

    auto layout = new QVBoxLayout(this);
    
    m_DeviceTree = new QTreeWidget(this);
    m_DeviceTree->setHeaderLabels(QStringList() << tr("ID") << tr("Model") << tr("SDK version") << tr("Platform version") << tr("Status"));
    m_DeviceTree->setRootIsDecorated(false);
    m_DeviceTree->setSelectionMode(QAbstractItemView::SingleSelection);
    m_DeviceTree->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_DeviceTree->header()->setStretchLastSection(false);
    m_DeviceTree->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_DeviceTree->header()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_DeviceTree->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    m_DeviceTree->header()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    m_DeviceTree->header()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    layout->addWidget(m_DeviceTree);

    // Create buttons in order: Refresh, Install, Cancel
    m_RefreshButton = new QPushButton(tr("Refresh"), this);
    m_InstallButton = new QPushButton(tr("Install"), this);
    auto cancelButton = new QPushButton(tr("Cancel"), this);
    
    m_InstallButton->setDefault(true);
    m_InstallButton->setEnabled(false);
    
    connect(m_RefreshButton, &QPushButton::clicked, this, &DeviceSelectionDialog::refreshDevices);
    connect(m_InstallButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    connect(m_DeviceTree, &QTreeWidget::itemSelectionChanged, this, &DeviceSelectionDialog::updateInstallButtonState);
    
    // Layout buttons in order: Refresh, Install, Cancel
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_RefreshButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_InstallButton);
    buttonLayout->addWidget(cancelButton);
    
    layout->addLayout(buttonLayout);
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(2);

    refreshDevices();
}

QString DeviceSelectionDialog::selectedDeviceSerial() const
{
    auto selected = m_DeviceTree->selectedItems();
    if (selected.isEmpty()) {
        return QString();
    }
    return selected.first()->data(0, Qt::UserRole).toString();
}

void DeviceSelectionDialog::refreshDevices()
{
    m_DeviceTree->clear();
    m_Devices.clear();
    m_RefreshButton->setEnabled(false);
    startDeviceListWorker();
}

void DeviceSelectionDialog::startDeviceListWorker()
{
    // Show indeterminate progress dialog
    if (!m_ProgressDialog) {
        m_ProgressDialog = new QProgressDialog(this);
        m_ProgressDialog->setCancelButton(nullptr);
        m_ProgressDialog->setRange(0, 0); // Indeterminate
        m_ProgressDialog->setLabelText(tr("Refreshing..."));
        m_ProgressDialog->setWindowFlags(m_ProgressDialog->windowFlags() & ~Qt::WindowCloseButtonHint);
        m_ProgressDialog->setWindowTitle(tr("Loading devices"));
        m_ProgressDialog->setModal(true);
    }
    m_ProgressDialog->show();
    
    auto thread = new QThread(this);
    auto worker = new DeviceListWorker();
    worker->moveToThread(thread);
    
    connect(thread, &QThread::started, worker, &DeviceListWorker::listDevices);
    connect(worker, &DeviceListWorker::devicesListed, this, &DeviceSelectionDialog::handleDevicesListed);
    connect(worker, &DeviceListWorker::error, this, &DeviceSelectionDialog::handleDeviceListError);
    connect(worker, &DeviceListWorker::finished, thread, &QThread::quit);
    connect(worker, &DeviceListWorker::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, this, &DeviceSelectionDialog::handleWorkerFinished);
    
    thread->start();
}

void DeviceSelectionDialog::handleWorkerFinished()
{
    m_RefreshButton->setEnabled(true);
    if (m_ProgressDialog) {
        m_ProgressDialog->hide();
    }
}

void DeviceSelectionDialog::handleDevicesListed(const QList<DeviceInfo> &devices)
{
    m_Devices = devices;
    
    if (m_Devices.isEmpty()) {
        QMessageBox::information(this, tr("No devices"), tr("No devices found. Please connect a device and enable USB debugging."));
        return;
    }
    
    // Only allow installation if at least one device is in "device" status
    bool hasInstallableDevice = false;
    for (const DeviceInfo &device : m_Devices) {
        if (device.status == "device") {
            hasInstallableDevice = true;
            break;
        }
    }
    
    if (!hasInstallableDevice) {
        QMessageBox::information(this, tr("No installable devices"), tr("No devices are in a state that allows installation. Please ensure at least one device is connected and authorized."));
    }

    populateDeviceList(m_Devices);
}

void DeviceSelectionDialog::handleDeviceListError(const QString &message)
{
    QMessageBox::warning(this, tr("Error"), message);
}

void DeviceSelectionDialog::populateDeviceList(const QList<DeviceInfo> &devices)
{
    for (const DeviceInfo &device : devices) {
        auto item = new QTreeWidgetItem(m_DeviceTree);
        item->setData(0, Qt::UserRole, device.serial);
        item->setText(0, device.serial);
        item->setText(1, device.model.isEmpty() ? tr("Unknown") : device.model);
        item->setText(2, device.androidSdkVersion.isEmpty() ? tr("Unknown") : device.androidSdkVersion);
        item->setText(3, device.androidVersion.isEmpty() ? tr("Unknown") : device.androidVersion);
        item->setText(4, translateStatus(device.status));
    }
    
    if (m_DeviceTree->topLevelItemCount() > 0) {
        m_DeviceTree->setCurrentItem(m_DeviceTree->topLevelItem(0));
    }
    
    updateInstallButtonState();
}

void DeviceSelectionDialog::updateInstallButtonState()
{
    auto selected = m_DeviceTree->selectedItems();
    if (selected.isEmpty()) {
        m_InstallButton->setEnabled(false);
        return;
    }
    QString serial = selected.first()->data(0, Qt::UserRole).toString();
    // Find the device and check if it's in "device" status
    bool canInstall = false;
    for (const DeviceInfo &device : m_Devices) {
        if (device.serial == serial && device.status == "device") {
            canInstall = true;
            break;
        }
    }
    m_InstallButton->setEnabled(canInstall);
}

QString DeviceSelectionDialog::translateStatus(const QString &status) const
{
    if (status == "device") {
        return tr("Connected");
    } else if (status == "offline") {
        return tr("Offline");
    } else if (status == "unauthorized") {
        return tr("Unauthorized");
    } else if (status == "bootloader") {
        return tr("Bootloader");
    } else if (status == "recovery") {
        return tr("Recovery");
    } else if (status == "sideload") {
        return tr("Sideload");
    } else if (status == "authorizing") {
        return tr("Authorizing");
    } else if (status == "no permissions") {
        return tr("No Permissions");
    } else if (status == "host") {
        return tr("Host");
    } else {
        // Return capitalized version of unknown status
        if (status.isEmpty()) {
            return tr("Unknown");
        }
        return status.at(0).toUpper() + status.mid(1);
    }
}
