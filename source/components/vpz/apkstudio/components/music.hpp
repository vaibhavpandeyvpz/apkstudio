#ifndef VPZ_APKSTUDIO_COMPONENTS_MUSIC_HPP
#define VPZ_APKSTUDIO_COMPONENTS_MUSIC_HPP

#include <QTreeWidget>
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Music : public QTreeWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QString device;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("music", key);
    }
public:
    explicit Music(const QString &, QWidget * = 0);
    ~Music();
public slots:
    void onInitComplete();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_MUSIC_HPP
