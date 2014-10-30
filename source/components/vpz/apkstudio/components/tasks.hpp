#ifndef VPZ_APKSTUDIO_COMPONENTS_TASKS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_TASKS_HPP

#include <QListWidget>
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "dockable.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Tasks : public Dockable
{
    Q_OBJECT
private:
    QListWidget *list;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("tasks", key);
    }
public:
    explicit Tasks(QWidget *parent = 0);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_TASKS_HPP
