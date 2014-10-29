#ifndef VPZ_APKSTUDIO_WINDOWS_IDE_HPP
#define VPZ_APKSTUDIO_WINDOWS_IDE_HPP

#include <QCloseEvent>
#include <QDesktopServices>
#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStatusBar>
#include "components/devices.hpp"
#include "components/editor.hpp"
#include "components/files.hpp"
#include "components/outline.hpp"
#include "components/output.hpp"
#include "components/projects.hpp"
#include "components/tasks.hpp"
#include "helpers/adb.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "resources/constant.hpp"
#include "menubar.hpp"
#include "toolbar.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

class IDE : public QMainWindow
{
    Q_OBJECT
private:
    int exit_code;
    QList<QMetaObject::Connection> connections;
    Components::Devices *devices;
    Components::Editor *editor;
    Components::Files *files;
    MenuBar *menu_bar;
    QStandardItemModel *opened;
    Components::Outline *outline;
    Components::Output *output;
    Components::Projects *projects;
    Components::Tasks *tasks;
    ToolBar *tool_bar;
    QStatusBar *status_bar;
private:
    void closeEvent(QCloseEvent *event);
    void setupDocks();
    static QString translate(const char *key) {
        return Helpers::Text::translate("ide", key);
    }
public:
    explicit IDE(QWidget *parent = 0);
    ~IDE();
public Q_SLOTS:
    void onActionAdbKill();
    void onActionAdbStart();
    void onActionContribute();
    void onActionDonate();
    void onActionFeedbackIssues();
    void onActionFeedbackThanks();
    void onActionFirst();
    void onActionLast();
    void onActionNext();
    void onActionPrevious();
    void onActionQuit();
    void onActionRestart();
    void onActionToggle(QAction *);
    void onInitComplete();
signals:
    void viewToggled(const char *id, bool visible);
};

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WINDOWS_IDE_HPP
