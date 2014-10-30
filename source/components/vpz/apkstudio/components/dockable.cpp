#include "dockable.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Dockable::Dockable(const QString &title, QWidget *parent) :
    QDockWidget(title, parent)
{
    setContentsMargins(2, 2, 2, 2);
}

Dockable::~Dockable()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
