#ifndef VPZ_APKSTUDIO_COMPONENTS_RECENTS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_RECENTS_HPP

#include <QFileInfo>
#include <QMenu>
#include "helpers/settings.hpp"
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Recents : public QMenu
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("menubar", key);
    }
public:
    explicit Recents(QObject *, QWidget * = 0);
    ~Recents();
signals:
    void recentSelected(QFileInfo);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_RECENTS_HPP
