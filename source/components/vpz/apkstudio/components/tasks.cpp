#include "tasks.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Tasks::Tasks(QWidget *parent) :
    QDockWidget(translate("title_dock"), parent)
{
    QWidget *widget = new QWidget(this);
    widget->setMinimumSize(64, 64);
    setObjectName("tasks");
    setWidget(widget);
}

Tasks::~Tasks()
{
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
