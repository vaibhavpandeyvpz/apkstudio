#ifndef VPZ_APKSTUDIO_COMPONENTS_EDITOR_HPP
#define VPZ_APKSTUDIO_COMPONENTS_EDITOR_HPP

#include <QWidget>
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Editor : public QWidget
{
    Q_OBJECT
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("editor", key);
    }
public:
    explicit Editor(QWidget *parent = 0);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_EDITOR_HPP
