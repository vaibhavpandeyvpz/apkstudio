#ifndef VPZ_APKSTUDIO_WINDOWS_INFORMATION_HPP
#define VPZ_APKSTUDIO_WINDOWS_INFORMATION_HPP

#include <QLineEdit>
#include <QFormLayout>
#include <QTabWidget>
#include <QVBoxLayout>
#include "helpers/adb.hpp"
#include "helpers/format.hpp"
#include "helpers/text.hpp"
#include "resources/embedded.hpp"
#include "dialog.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

class Information : public Dialog
{
    Q_OBJECT
private:
    QString device;
    QTabWidget *tabs;
private:
    void createHardwareTab();
    void createNetworkTab();
    void createSoftwareTab();
    static QString translate(const char *key) {
        return Helpers::Text::translate("information", key);
    }
public:
    explicit Information(const QString &, QWidget * = 0);
public slots:
    void onInitComplete();
signals:
    void updateIMEI(QString);
    void updateInformation(QMap<QString, QString>);
};

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WINDOWS_INFORMATION_HPP
