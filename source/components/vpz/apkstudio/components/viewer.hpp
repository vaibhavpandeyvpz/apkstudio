#ifndef VPZ_APKSTUDIO_COMPONENTS_VIEWER_HPP
#define VPZ_APKSTUDIO_COMPONENTS_VIEWER_HPP

#include <QAction>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QMenu>
#include <QPixmap>
#include <QScrollArea>
#include <QScrollBar>
#include "helpers/flickcharm.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "resources/embedded.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Viewer : public QScrollArea
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QString path;
    double scale;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("viewer", key);
    }
    void zoom(const double);
protected:
    QLabel *image;
    Helpers::FlickCharm *flick_charm;
protected:
    void keyPressEvent(QKeyEvent *);
public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();
    inline bool open(const char *path) { return open(QString(path)); }
    inline bool open(const QString &path) { return open(QFileInfo(path)); }
    bool open(const QFileInfo &);
    bool save();
    void scrollfix();
    inline void zoomIn() { zoom(1.25); }
    inline void zoomOut() { zoom(0.8); }
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_VIEWER_HPP
