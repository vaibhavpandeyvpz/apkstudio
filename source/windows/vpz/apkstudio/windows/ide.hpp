#ifndef VPZ_APKSTUDIO_WINDOWS_IDE_HPP
#define VPZ_APKSTUDIO_WINDOWS_IDE_HPP

#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QStatusBar>
#include "resources/constant.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
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
    MenuBar *menu_bar;
    ToolBar *tool_bar;
    QStatusBar *status_bar;
private:
    void closeEvent(QCloseEvent *event);
    static QString translate(const char *key) {
        return Helpers::Text::translate("ide", key);
    }
public:
    explicit IDE(QWidget *parent = 0);
public Q_SLOTS:
    void onActionQuit();
    void onActionRestart();
    void onActionToggle(QAction *);
    void onInitComplete();
};

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WINDOWS_IDE_HPP
