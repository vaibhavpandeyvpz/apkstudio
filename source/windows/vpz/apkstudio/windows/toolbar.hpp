#ifndef VPZ_APKSTUDIO_WINDOWS_TOOLBAR_HPP
#define VPZ_APKSTUDIO_WINDOWS_TOOLBAR_HPP

#include <QAction>
#include <QComboBox>
#include <QToolBar>
#include "helpers/macro.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "resources/embedded.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

class ToolBar : public QToolBar
{
    Q_OBJECT
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("toolbar", key);
    }
    void refreshEncodings(QComboBox *combo);
public:
    explicit ToolBar(QWidget *parent = 0);
};

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WINDOWS_TOOLBAR_HPP
