#include "files.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Files::Files(QWidget *parent) :
    QDockWidget(translate("title_dock"), parent)
{
    QWidget *widget = new QWidget(this);
    widget->setMinimumSize(64, 64);
    setObjectName("files");
    setWidget(widget);
}

Files::~Files()
{
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
