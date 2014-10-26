#ifndef VPZ_APKSTUDIO_COMPONENTS_DEVICECHOOSER_HPP
#define VPZ_APKSTUDIO_COMPONENTS_DEVICECHOOSER_HPP

#include <QAction>
#include <QDesktopServices>
#include <QFileDialog>
#include <QHeaderView>
#include <QMenu>
#include <QProcess>
#include <QStandardItemModel>
#include <QToolBar>
#include <QToolButton>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>
#include "helpers/adb.hpp"
#include "helpers/format.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "resources/constant.hpp"
#include "resources/embedded.hpp"
#include "resources/variant.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class DeviceChooser : public QWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QTreeView *tree;
    QStandardItemModel *model;
private:
    static QIcon icon(const char *name) {
        return Resources::Embedded::icon(name);
    }
    Resources::Device selected() const;
    static QString translate(const char *key) {
        return Helpers::Text::translate("device_chooser", key);
    }
private Q_SLOTS:
    void onBrowse();
    void onInformation();
    void onLogcat();
    void onRefresh();
    void onScreenshot();
    void onShell();
public:
    explicit DeviceChooser(QWidget *parent = 0);
    ~DeviceChooser();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_DEVICECHOOSER_HPP
