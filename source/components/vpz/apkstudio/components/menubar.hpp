#ifndef VPZ_APKSTUDIO_COMPONENTS_MENUBAR_HPP
#define VPZ_APKSTUDIO_COMPONENTS_MENUBAR_HPP

#include <QMenuBar>
#include "helpers/macro.hpp"
#include "helpers/text.hpp"
#include "recents.hpp"
#include "scripts.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class MenuBar : public QMenuBar
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("menubar", key);
    }
public:
    explicit MenuBar(QWidget * = 0);
    ~MenuBar();
public slots:
    void onViewToggled(const char *, const bool);
signals:
    void viewToggled(const char *, bool);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_MENUBAR_HPP
