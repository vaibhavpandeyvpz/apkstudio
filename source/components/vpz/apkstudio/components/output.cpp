#include "output.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Output::Output(QWidget *parent) :
    QDockWidget(translate("title_dock"), parent)
{
    QWidget *widget = new QWidget(this);
    widget->setMinimumSize(64, 64);
    setContentsMargins(2, 2, 2, 2);
    setObjectName("output");
    setWidget(widget);
}

Output::~Output()
{
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
