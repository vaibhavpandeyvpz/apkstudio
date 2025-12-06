#ifndef DEVICELISTWORKER_H
#define DEVICELISTWORKER_H

#include <QList>
#include <QObject>
#include <QString>

struct DeviceInfo {
    QString serial;
    QString status;
    QString model;
    QString androidSdkVersion;
    QString androidVersion;
};

class DeviceListWorker : public QObject
{
    Q_OBJECT
public:
    explicit DeviceListWorker(QObject *parent = nullptr);
    void listDevices();
signals:
    void finished();
    void devicesListed(const QList<DeviceInfo> &devices);
    void error(const QString &message);
    void started();
private:
    DeviceInfo parseDeviceLine(const QString &line);
    QString getDeviceProperty(const QString &serial, const QString &property);
};

#endif // DEVICELISTWORKER_H

