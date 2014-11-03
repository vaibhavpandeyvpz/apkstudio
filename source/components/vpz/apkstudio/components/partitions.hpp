#ifndef VPZ_APKSTUDIO_COMPONENTS_PARTITIONS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_PARTITIONS_HPP

#include <QTreeWidget>
#include "helpers/text.hpp"

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
    static QString translate(const char *key) {
        return Helpers::Text::translate("partitions", key);
    }
public:
    explicit Partitions(const QString &, QWidget * = 0);
    ~Partitions();
public slots:
    void onInitComplete();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_PARTITIONS_HPP
