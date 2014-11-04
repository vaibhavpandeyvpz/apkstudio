#ifndef VPZ_APKSTUDIO_COMPONENTS_APPLICATIONS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_APPLICATIONS_HPP

#include <QAction>
#include <QTreeWidget>
#include "helpers/adb.hpp"
#include "helpers/text.hpp"
#include "resources/embedded.hpp"
#include "resources/variant.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Applications : public QTreeWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QString device;
private:
    void onDetails();
    void onDisable();
    void onEnable();
    void onInstall();
    void onPull();
    void onUninstall();
    static QString translate(const char *key) {
        return Helpers::Text::translate("applications", key);
    }
public:
    enum {
        ACTION_DETAILS = 1,
        ACTION_DISABLE,
        ACTION_ENABLE,
        ACTION_INSTALL,
        ACTION_PULL,
        ACTION_UNINSTALL
    };
    explicit Applications(const QString &, QWidget * = 0);
    ~Applications();
public slots:
    void onAction(QAction *);
    void onInitComplete();
    void onRefresh();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_APPLICATIONS_HPP
