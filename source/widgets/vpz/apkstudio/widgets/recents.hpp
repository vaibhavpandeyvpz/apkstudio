#ifndef VPZ_APKSTUDIO_WIDGETS_RECENTS_HPP
#define VPZ_APKSTUDIO_WIDGETS_RECENTS_HPP

#include <QMenu>
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Widgets {

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

} // namespace Widgets
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WIDGETS_RECENTS_HPP
