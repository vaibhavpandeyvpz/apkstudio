#include "outline.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Outline::Outline(QWidget *parent) :
    QDockWidget(translate("title_dock"), parent)
{
    QWidget *widget = new QWidget(this);
    widget->setMinimumSize(64, 64);
    setObjectName("outline");
    setWidget(widget);
}

Outline::~Outline()
{
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
