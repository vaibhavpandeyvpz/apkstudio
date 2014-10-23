#ifndef VPZ_APKSTUDIO_HELPERS_FLICKCHARM_HPP
#define VPZ_APKSTUDIO_HELPERS_FLICKCHARM_HPP

#include <QObject>

class QWidget;

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class FlickCharmPrivate;

class FlickCharm: public QObject
{
    Q_OBJECT
public:
    FlickCharm(QObject *parent = 0);
    ~FlickCharm();
    void activateOn(QWidget *widget);
    void deactivateFrom(QWidget *widget);
    bool eventFilter(QObject *object, QEvent *event);
protected:
    void timerEvent(QTimerEvent *event);
private:
    FlickCharmPrivate *d;
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_FLICKCHARM_HPP
