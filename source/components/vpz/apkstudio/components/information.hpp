#ifndef VPZ_APKSTUDIO_COMPONENTS_INFORMATION_HPP
#define VPZ_APKSTUDIO_COMPONENTS_INFORMATION_HPP

#include <QLineEdit>
#include <QFormLayout>
#include <QTabWidget>
#include "helpers/adb.hpp"
#include "helpers/format.hpp"
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Information : public QTabWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
private:
    void inflateHardware();
    void inflateNetwork();
    void inflateSoftware();
    static QString translate(const char *key) {
        return Helpers::Text::translate("information", key);
    }
public:
    explicit Information(QWidget *parent = 0);
    void setDevice(const QString &);
    ~Information();
signals:
    void updateIMEI(const QString &);
    void updateInformation(const QMap<QString, QString> &);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_INFORMATION_HPP
