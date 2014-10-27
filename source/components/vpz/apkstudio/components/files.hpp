#ifndef VPZ_APKSTUDIO_COMPONENTS_FILES_HPP
#define VPZ_APKSTUDIO_COMPONENTS_FILES_HPP

#include <QDockWidget>
#include "helpers/settings.hpp"
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Files : public QDockWidget
{
    Q_OBJECT
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("files", key);
    }
public:
    explicit Files(QWidget *parent = 0);
    ~Files();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_FILES_HPP
