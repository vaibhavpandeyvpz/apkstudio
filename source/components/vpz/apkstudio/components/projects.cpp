#include "projects.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Projects::Projects(QWidget *parent) :
    QDockWidget(translate("title_dock"), parent)
{
    QWidget *widget = new QWidget(this);
    widget->setMinimumSize(64, 64);
    setObjectName("projects");
    setWidget(widget);
}

Projects::~Projects()
{
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
