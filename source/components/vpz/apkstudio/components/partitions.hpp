#ifndef VPZ_APKSTUDIO_COMPONENTS_PARTITIONS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_PARTITIONS_HPP

#include <QAction>
#include <QMessageBox>
#include <QTreeWidget>
#include "helpers/adb.hpp"
#include "helpers/text.hpp"
#include "resources/embedded.hpp"
#include "resources/variant.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Partitions : public QTreeWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QString device;
private:
    void onRemount();
    void onUnmount();
    static QString translate(const char *key) {
        return Helpers::Text::translate("partitions", key);
    }
    QVector<Resources::Partition> selected();
public:
    enum {
        ACTION_REMOUNT = 1,
        ACTION_UNMOUNT
    };
    explicit Partitions(const QString &, QWidget * = 0);
    ~Partitions();
public slots:
    void onAction(QAction *);
    void onRefresh();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_PARTITIONS_HPP
