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
#include "helpers/adb.hpp"
#include "helpers/format.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "resources/constant.hpp"
#include "resources/embedded.hpp"
#include "resources/variant.hpp"
#include "dockable.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Devices : public Dockable
{
    Q_OBJECT
private:
    QTreeWidget *tree;
private:
    Resources::Device selected() const;
    static QString translate(const char *key) {
        return Helpers::Text::translate("devices", key);
    }
private slots:
    void onExplore();
    void onInformation();
    void onLogcat();
    void onRefresh();
    void onScreenshot();
    void onShell();
public:
    explicit Devices(QWidget *parent = 0);
signals:
    void showExplorer(QString);
    void showInformation(QString);
    void showLogcat(QString);
};

}
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_DEVICES_HPP
