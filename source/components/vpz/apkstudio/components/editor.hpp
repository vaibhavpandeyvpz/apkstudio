#ifndef VPZ_APKSTUDIO_COMPONENTS_EDITOR_HPP
#define VPZ_APKSTUDIO_COMPONENTS_EDITOR_HPP

#include <QComboBox>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QHBoxLayout>
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
    QComboBox *extra;
    QComboBox *files;
    QComboBox *symbols;
    QStackedWidget *stack;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("editor", key);
    }
public:
    explicit Editor(QWidget *parent = 0);
    inline void setModel(QStandardItemModel *model) { files->setModel(model); }
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_EDITOR_HPP
