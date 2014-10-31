#include "statusbar.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

StatusBar *StatusBar::self = nullptr;

StatusBar::StatusBar(QWidget *parent) :
    QStatusBar(parent)
{
    self = this;
}

StatusBar *StatusBar::instance()
{
    return self;
}

StatusBar::~StatusBar()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
