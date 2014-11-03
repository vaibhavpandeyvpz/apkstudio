#ifndef VPZ_APKSTUDIO_COMPONENTS_STORAGE_HPP
#define VPZ_APKSTUDIO_COMPONENTS_STORAGE_HPP

#include <QTreeWidget>
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Storage : public QTreeWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QString device;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("storage", key);
    }
public:
    explicit Storage(const QString &, QWidget * = 0);
    ~Storage();
public slots:
    void onInitComplete();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_STORAGE_HPP
