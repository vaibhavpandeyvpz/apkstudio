#ifndef VPZ_APKSTUDIO_COMPONENTS_DEVICEINFORMATION_HPP
#define VPZ_APKSTUDIO_COMPONENTS_DEVICEINFORMATION_HPP

#include <QLineEdit>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include "helpers/adb.hpp"
#include "helpers/format.hpp"
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class DeviceInformation : public QGridLayout
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("device_information", key);
    }
public:
    explicit DeviceInformation(QWidget *parent = 0);
    void setDevice(const QString &);
    ~DeviceInformation();
signals:
    void updateIMEI(const QString &);
    void updateInformation(const QMap<QString, QString> &);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_DEVICEINFORMATION_HPP
