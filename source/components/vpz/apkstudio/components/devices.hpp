#ifndef VPZ_APKSTUDIO_COMPONENTS_DEVICES_HPP
#define VPZ_APKSTUDIO_COMPONENTS_DEVICES_HPP

#include <QAction>
#include <QDesktopServices>
#include <QFileDialog>
#include <QHeaderView>
#include <QMenu>
#include <QProcess>
#include <QToolBar>
#include <QToolButton>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QDockWidget>
#include "helpers/adb.hpp"
#include "helpers/format.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "resources/constant.hpp"
#include "resources/embedded.hpp"
#include "resources/variant.hpp"
#include "dialog.hpp"
#include "information.hpp"
#include "logcat.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Devices : public QDockWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QTreeWidget *tree;
private:
    static QIcon icon(const char *name) {
        return Resources::Embedded::icon(name);
    }
    Resources::Device selected() const;
    static QString translate(const char *key) {
        return Helpers::Text::translate("devices", key);
    }
private Q_SLOTS:
    void onBrowse();
    void onInformation();
    void onLogcat();
    void onRefresh();
    void onScreenshot();
    void onShell();
public:
    explicit Devices(QWidget *parent = 0);
    ~Devices();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_DEVICES_HPP
