#ifndef VPZ_APKSTUDIO_COMPONENTS_EDITOR_HPP
#define VPZ_APKSTUDIO_COMPONENTS_EDITOR_HPP

#include <QAbstractItemView>
#include <QComboBox>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QToolBar>
#include <QTabWidget>
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "coder.hpp"
#include "viewer.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Editor : public QWidget
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QComboBox *files;
    QComboBox *variants;
    QStringList editables;
    QTabWidget *tabs;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("editor", key);
    }
public:
    explicit Editor(QStandardItemModel *, QWidget * = 0);
    void close();
    void first();
    void last();
    void next();
    void open(const QString &path) { return open(QFileInfo(path)); }
    void open(const QFileInfo &);
    void previous();
    void save(const bool = false);
    ~Editor();
public slots:
    void onSelectionChanged(int);
signals:
    void selectionChanged(int);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_EDITOR_HPP
