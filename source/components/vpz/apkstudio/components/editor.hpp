#ifndef VPZ_APKSTUDIO_COMPONENTS_EDITOR_HPP
#define VPZ_APKSTUDIO_COMPONENTS_EDITOR_HPP

#include <QComboBox>
#include <QFileInfo>
#include <QStackedWidget>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QToolBar>
#include <QWidget>
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
    QComboBox *symbols;
    QComboBox *variants;
    QStackedWidget *stack;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("editor", key);
    }
public:
    explicit Editor(QWidget * = 0);
    void first();
    void last();
    void next();
    void open(const QString &);
    void previous();
    inline void setModel(QAbstractItemModel *model) { files->setModel(model); }
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
