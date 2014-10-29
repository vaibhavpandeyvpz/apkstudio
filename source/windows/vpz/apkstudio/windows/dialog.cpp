#include "dialog.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    setMinimumSize(480, 320);
#ifdef Q_OS_WIN
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
}

Dialog::~Dialog()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ
