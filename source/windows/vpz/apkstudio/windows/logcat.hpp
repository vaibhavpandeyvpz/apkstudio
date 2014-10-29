#ifndef VPZ_APKSTUDIO_WINDOWS_LOGCAT_HPP
#define VPZ_APKSTUDIO_WINDOWS_LOGCAT_HPP

#include <QAction>
#include <QRegularExpression>
#include <QToolBar>
#include <QTreeWidget>
#include <QVBoxLayout>
#include "helpers/adb.hpp"
#include "helpers/realtime.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "resources/embedded.hpp"
#include "resources/variant.hpp"
#include "dialog.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

class Logcat : public Dialog
{
    Q_OBJECT
private:
    bool debug;
    QString device;
    bool error;
    bool info;
    Helpers::Realtime *receiver;
    QRegularExpression regex;
    bool scroll;
    bool verbose;
    bool warning;
    QTreeWidget *tree;
protected:
    void closeEvent(QCloseEvent *);
private:
    void createReceiver();
    void createToolbar();
    void createTree();
    static QString translate(const char *key) {
        return Helpers::Text::translate("logcat", key);
    }
private slots:
    void onLineRead(const QString &);
    void onStateChanged(const bool);
public:
    explicit Logcat(const QString &, QWidget * = 0);
signals:
    void stateChanged(bool);
};

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WINDOWS_LOGCAT_HPP
