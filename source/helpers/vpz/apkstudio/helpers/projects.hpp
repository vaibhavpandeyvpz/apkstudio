#ifndef VPZ_APKSTUDIO_HELPERS_PROJECTS_HPP
#define VPZ_APKSTUDIO_HELPERS_PROJECTS_HPP

#include <QDir>
#include <QFileInfo>
#include <QStandardItemModel>
#include "resources/embedded.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class Projects : public QStandardItemModel
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QStringList directories;
    QStringList files;
public:
    explicit Projects(QObject * = 0);
    inline bool close(const QString &path) { return close(QFileInfo(path)); }
    bool close(const QFileInfo &);
    inline bool open(const QString &path) { return open(QFileInfo(path)); }
    bool open(const QFileInfo &);
    void refresh(QStandardItem *);
    ~Projects();
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_PROJECTS_HPP
