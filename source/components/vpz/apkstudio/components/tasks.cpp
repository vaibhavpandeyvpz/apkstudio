#include "tasks.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Tasks::Tasks(QWidget *parent) :
    QDockWidget(translate("title_dock"), parent)
{
    list = new QListWidget(this);
    list->setMinimumSize(64, 64);
    setContentsMargins(2, 2, 2, 2);
    setObjectName("tasks");
    setWidget(list);
}

Tasks::~Tasks()
{
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
