#ifndef VPZ_APKSTUDIO_COMPONENTS_INFORMATION_HPP
#define VPZ_APKSTUDIO_COMPONENTS_INFORMATION_HPP

#include <QWidget>
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Information : public QWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QString device;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("information", key);
    }
public:
    explicit Information(const QString &, QWidget * = 0);
    ~Information();
public slots:
    void onRefresh();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_INFORMATION_HPP
