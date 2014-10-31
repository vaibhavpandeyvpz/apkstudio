#ifndef VPZ_APKSTUDIO_COMPONENTS_STATUSBAR_HPP
#define VPZ_APKSTUDIO_COMPONENTS_STATUSBAR_HPP

#include <QStatusBar>

namespace VPZ {
namespace APKStudio {
namespace Components {

class StatusBar : public QStatusBar
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    static StatusBar *self;
public:
    explicit StatusBar(QWidget *parent = 0);
    static StatusBar *instance();
    ~StatusBar();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_STATUSBAR_HPP
