#ifndef VPZ_APKSTUDIO_WINDOWS_IDE_HPP
#define VPZ_APKSTUDIO_WINDOWS_IDE_HPP

#include <QCloseEvent>
#include <QDesktopServices>
#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include "components/devices.hpp"
#include "components/editor.hpp"
#include "components/files.hpp"
#include "components/menubar.hpp"
#include "components/outline.hpp"
#include "components/output.hpp"
#include "components/projects.hpp"
#include "components/tasks.hpp"
#include "components/statusbar.hpp"
#include "components/toolbar.hpp"
#include "helpers/adb.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "resources/constant.hpp"
#include "explorer.hpp"
#include "information.hpp"
#include "logcat.hpp"
#include "settings.hpp"

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
    Components::MenuBar *menu_bar;
    QStandardItemModel *opened;
    Components::Outline *outline;
    Components::Output *output;
    Components::Projects *projects;
    Components::Tasks *tasks;
    Components::ToolBar *tool_bar;
    Components::StatusBar *status_bar;
private:
    void closeEvent(QCloseEvent *event);
    void setDocks();
    static QString translate(const char *key) {
        return Helpers::Text::translate("ide", key);
    }
public:
    explicit IDE(QWidget * = 0);
    ~IDE();
public slots:
    void onActionAdbKill();
    void onActionAdbStart();
    void onActionCloseFile();
    void onActionContribute();
    void onActionDonate();
    void onActionFeedbackIssues();
    void onActionFeedbackThanks();
    void onActionFirst();
    void onActionLast();
    void onActionNext();
    void onActionOpenApk();
    void onActionOpenFile();
    void onActionOpenProject();
    void onActionPrevious();
    void onActionQuit();
    void onActionRestart();
    void onActionSave();
    void onActionSaveAll();
    void onActionSettings();
    void onActionToggle(QAction *);
    void onInitComplete();
    void onShowExplorer(const QString &);
    void onShowInformation(const QString &);
    void onShowLogcat(const QString &);
signals:
    void viewToggled(const char *, bool);
};

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WINDOWS_IDE_HPP
