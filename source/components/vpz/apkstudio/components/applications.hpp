#ifndef VPZ_APKSTUDIO_COMPONENTS_APPLICATIONS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_APPLICATIONS_HPP

#include <QTreeWidget>
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Applications : public QTreeWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QString device;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("applications", key);
    }
public:
    explicit Applications(const QString &, QWidget * = 0);
    ~Applications();
public slots:
    void onInitComplete();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_APPLICATIONS_HPP
