#include "tasks.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Tasks::Tasks(QWidget *parent) :
    Dockable(translate("title_dock"), parent)
{
    list = new QListWidget(this);
    list->setMinimumSize(64, 64);
    setObjectName("tasks");
    setWidget(list);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
