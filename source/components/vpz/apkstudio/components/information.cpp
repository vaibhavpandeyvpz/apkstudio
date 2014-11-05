#include "information.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Information::Information(const QString &device, QWidget *parent) :
    QWidget(parent), device(device)
{
}

void Information::onRefresh()
{
}

Information::~Information()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
