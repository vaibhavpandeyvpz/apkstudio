#ifndef VPZ_APKSTUDIO_WINDOWS_CHMOD_HPP
#define VPZ_APKSTUDIO_WINDOWS_CHMOD_HPP

#include <QBoxLayout>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QWidget>
#include "helpers/adb.hpp"
#include "helpers/text.hpp"
#include "resources/embedded.hpp"
#include "resources/variant.hpp"
#include "dialog.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

class CHMOD : public Dialog
{
    Q_OBJECT
private:
    QString device;
    Resources::File file;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("chmod", key);
    }
public:
    explicit CHMOD(const QString &, const Resources::File &, QWidget * = 0);
};

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WINDOWS_CHMOD_HPP
