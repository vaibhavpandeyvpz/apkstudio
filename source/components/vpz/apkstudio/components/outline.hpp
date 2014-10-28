#ifndef VPZ_APKSTUDIO_COMPONENTS_OUTLINE_HPP
#define VPZ_APKSTUDIO_COMPONENTS_OUTLINE_HPP

#include <QDockWidget>
#include <QTreeWidget>
#include "helpers/settings.hpp"
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Outline : public QDockWidget
{
    Q_OBJECT
private:
    QTreeWidget *tree;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("outline", key);
    }
public:
    explicit Outline(QWidget *parent = 0);
    ~Outline();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_OUTLINE_HPP
