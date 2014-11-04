#ifndef VPZ_APKSTUDIO_COMPONENTS_STORAGE_HPP
#define VPZ_APKSTUDIO_COMPONENTS_STORAGE_HPP

#include <QAction>
#include <QTreeWidget>
#include <QVBoxLayout>
#include "helpers/adb.hpp"
#include "helpers/format.hpp"
#include "helpers/text.hpp"
#include "resources/variant.hpp"
#include "clearable.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Storage : public QTreeWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QString device;
    Clearable *path;
    QTreeWidget *tree;
private:
    void onCHMOD();
    void onCopy();
    void onCreate();
    void onDetails();
    void onMove();
    void onPull();
    void onPush();
    void onRemove();
    void onRename();
    static QString translate(const char *key) {
        return Helpers::Text::translate("storage", key);
    }
private slots:
    void onDoubleClicked(const QModelIndex &);
    void onRefresh();
public:
    enum {
        ACTION_CHMOD = 1,
        ACTION_COPY,
        ACTION_CREATE,
        ACTION_DETAILS,
        ACTION_MOVE,
        ACTION_PULL,
        ACTION_PUSH,
        ACTION_REMOVE,
        ACTION_RENAME
    };
    explicit Storage(const QString &, QWidget * = 0);
    ~Storage();
public slots:
    void onAction(QAction *);
    void onInitComplete();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_STORAGE_HPP
