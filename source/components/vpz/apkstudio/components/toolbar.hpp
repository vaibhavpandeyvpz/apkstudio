#ifndef VPZ_APKSTUDIO_COMPONENTS_TOOLBAR_HPP
#define VPZ_APKSTUDIO_COMPONENTS_TOOLBAR_HPP

#include <QAction>
#include <QToolBar>
#include "helpers/macro.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "resources/embedded.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class ToolBar : public QToolBar
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("toolbar", key);
    }
public:
    explicit ToolBar(QWidget * = 0);
    ~ToolBar();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_TOOLBAR_HPP
