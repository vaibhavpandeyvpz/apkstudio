#ifndef VPZ_APKSTUDIO_COMPONENTS_TASKS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_TASKS_HPP

#include <QDockWidget>
#include "helpers/settings.hpp"
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Tasks : public QDockWidget
{
    Q_OBJECT
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("tasks", key);
    }
public:
    explicit Tasks(QWidget *parent = 0);
    ~Tasks();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_TASKS_HPP
