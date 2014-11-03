#ifndef VPZ_APKSTUDIO_COMPONENTS_PHOTOS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_PHOTOS_HPP

#include <QTreeWidget>
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Photos : public QTreeWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QString device;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("photos", key);
    }
public:
    explicit Photos(const QString &, QWidget * = 0);
    ~Photos();
public slots:
    void onInitComplete();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_PHOTOS_HPP
