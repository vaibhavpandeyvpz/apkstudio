#include "files.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Files::Files(QWidget *parent) :
    QDockWidget(translate("title_dock"), parent)
{
    list = new QListView(this);
    list->setMinimumSize(64, 64);
    setContentsMargins(2, 2, 2, 2);
    setObjectName("files");
    setWidget(list);
}

Files::~Files()
{
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
