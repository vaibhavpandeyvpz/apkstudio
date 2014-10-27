#ifndef VPZ_APKSTUDIO_COMPONENTS_OUTPUT_HPP
#define VPZ_APKSTUDIO_COMPONENTS_OUTPUT_HPP

#include <QDockWidget>
#include "helpers/settings.hpp"
#include "helpers/text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Output : public QDockWidget
{
    Q_OBJECT
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("output", key);
    }
public:
    explicit Output(QWidget *parent = 0);
    ~Output();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_OUTPUT_HPP
