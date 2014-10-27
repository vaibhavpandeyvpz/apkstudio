#ifndef VPZ_APKSTUDIO_COMPONENTS_LOGCAT_HPP
#define VPZ_APKSTUDIO_COMPONENTS_LOGCAT_HPP

#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include "helpers/text.hpp"
#include "resources/embedded.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Logcat : public QWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    bool scroll;
    QTreeWidget *tree;
private:
    static QIcon icon(const char *name) {
        return Resources::Embedded::icon(name);
    }
    static QString translate(const char *key) {
        return Helpers::Text::translate("logcat", key);
    }
public:
    explicit Logcat(QWidget *parent = 0);
    void setDevice(const QString &);
    ~Logcat();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_LOGCAT_HPP
