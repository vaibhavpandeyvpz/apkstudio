#ifndef VPZ_APKSTUDIO_COMPONENTS_PROJECTS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_PROJECTS_HPP

#include <QDockWidget>
#include "helpers/settings.hpp"
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Projects : public QDockWidget
{
    Q_OBJECT
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("projects", key);
    }
public:
    explicit Projects(QWidget *parent = 0);
    ~Projects();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_PROJECTS_HPP
