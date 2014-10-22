#ifndef VPZ_APKSTUDIO_WINDOWS_MENUBAR_HPP
#define VPZ_APKSTUDIO_WINDOWS_MENUBAR_HPP

#include <QMenuBar>
#include "helpers/macro.hpp"
#include "helpers/text.hpp"
#include "widgets/recents.hpp"
#include "widgets/scripts.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

class MenuBar : public QMenuBar
{
    Q_OBJECT
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("menubar", key);
    }
public:
    explicit MenuBar(QWidget *parent = 0);
};

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WINDOWS_MENUBAR_HPP
