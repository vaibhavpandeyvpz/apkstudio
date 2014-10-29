#ifndef VPZ_APKSTUDIO_WINDOWS_EXPLORER_HPP
#define VPZ_APKSTUDIO_WINDOWS_EXPLORER_HPP

#include <QVBoxLayout>
#include "helpers/text.hpp"
#include "resources/embedded.hpp"
#include "dialog.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

class Explorer : public Dialog
{
    Q_OBJECT
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("explorer", key);
    }
private:
    QString device;
public:
    explicit Explorer(const QString &, QWidget * = 0);
};

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WINDOWS_EXPLORER_HPP
