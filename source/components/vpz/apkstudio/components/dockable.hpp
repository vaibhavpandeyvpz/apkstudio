#ifndef VPZ_APKSTUDIO_COMPONENTS_DOCKABLE_H
#define VPZ_APKSTUDIO_COMPONENTS_DOCKABLE_H

#include <QDockWidget>

namespace VPZ {
namespace APKStudio {
namespace Components {

class Dockable : public QDockWidget
{
    Q_OBJECT
protected:
    QList<QMetaObject::Connection> connections;
public:
    explicit Dockable(const QString &, QWidget * = 0);
    ~Dockable();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_DOCKABLE_H
