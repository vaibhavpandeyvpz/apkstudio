#include "explorer.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Windows {

Explorer::Explorer(const QString &device, QWidget *parent) :
    Dialog(parent), device(device)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(2, 2, 2, 2);
    layout->setSpacing(0);
    setLayout(layout);
    setWindowIcon(::icon("folder_stand"));
    setWindowTitle(translate("title_window").arg(device));
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ
