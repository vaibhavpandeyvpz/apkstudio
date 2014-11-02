#include "scripts.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Scripts::Scripts(QWidget *parent) :
    QMenu(translate("menu_scripts"), parent)
{
    setEnabled(false);
}

} // namespace Widgets
} // namespace APKStudio
} // namespace VPZ
