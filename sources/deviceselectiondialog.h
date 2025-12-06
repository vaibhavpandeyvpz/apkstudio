#ifndef DEVICESELECTIONDIALOG_H
#define DEVICESELECTIONDIALOG_H

#include <QDialog>
#include <QList>
#include <QProgressDialog>
#include <QPushButton>
#include <QString>
#include <QTreeWidget>
#include "devicelistworker.h"

class DeviceSelectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DeviceSelectionDialog(QWidget *parent = nullptr);
    QString selectedDeviceSerial() const;
    void refreshDevices();
private:
    QTreeWidget *m_DeviceTree;
    QPushButton *m_InstallButton;
    QPushButton *m_RefreshButton;
    QProgressDialog *m_ProgressDialog;
    QList<DeviceInfo> m_Devices;
    void populateDeviceList(const QList<DeviceInfo> &devices);
    void updateInstallButtonState();
    void startDeviceListWorker();
    QString translateStatus(const QString &status) const;
private slots:
    void handleDevicesListed(const QList<DeviceInfo> &devices);
    void handleDeviceListError(const QString &message);
    void handleWorkerFinished();
};

#endif // DEVICESELECTIONDIALOG_H

