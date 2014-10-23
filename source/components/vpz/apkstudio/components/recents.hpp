#ifndef VPZ_APKSTUDIO_COMPONENTS_RECENTS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_RECENTS_HPP

#include <QMenu>
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Recents : public QMenu
{
    Q_OBJECT
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("menubar", key);
    }
public:
    explicit Recents(QWidget *parent = 0);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_RECENTS_HPP
