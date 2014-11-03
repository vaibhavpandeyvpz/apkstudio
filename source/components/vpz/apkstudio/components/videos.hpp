#ifndef VPZ_APKSTUDIO_COMPONENTS_VIDEOS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_VIDEOS_HPP

#include <QTreeWidget>
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Videos : public QTreeWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QString device;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("videos", key);
    }
public:
    explicit Videos(const QString &, QWidget * = 0);
    ~Videos();
public slots:
    void onInitComplete();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_VIDEOS_HPP
