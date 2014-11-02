#ifndef VPZ_APKSTUDIO_COMPONENTS_SCRIPTS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_SCRIPTS_HPP

#include <QMenu>
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Scripts : public QMenu
{
    Q_OBJECT
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("menubar", key);
    }
public:
    explicit Scripts(QWidget * = 0);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_SCRIPTS_HPP
