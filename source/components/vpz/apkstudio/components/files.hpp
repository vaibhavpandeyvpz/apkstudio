#ifndef VPZ_APKSTUDIO_COMPONENTS_FILES_HPP
#define VPZ_APKSTUDIO_COMPONENTS_FILES_HPP

#include <QDockWidget>
#include <QListView>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include "helpers/settings.hpp"
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Files : public QDockWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QListView *list;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("files", key);
    }
public:
    explicit Files(QWidget * = 0);
    void setModel(QAbstractItemModel *);
    ~Files();
public slots:
    void onSelectionChanged(int);
signals:
    void selectionChanged(int);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_FILES_HPP
