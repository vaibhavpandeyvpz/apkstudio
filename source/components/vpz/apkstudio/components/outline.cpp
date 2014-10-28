#include "outline.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Outline::Outline(QWidget *parent) :
    QDockWidget(translate("title_dock"), parent)
{
    tree = new QTreeWidget(this);
    tree->setMinimumSize(64, 64);
    setContentsMargins(2, 2, 2, 2);
    setObjectName("outline");
    setWidget(tree);
}

Outline::~Outline()
{
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
