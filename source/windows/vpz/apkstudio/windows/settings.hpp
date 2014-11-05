#ifndef VPZ_APKSTUDIO_WINDOWS_SETTINGS_HPP
#define VPZ_APKSTUDIO_WINDOWS_SETTINGS_HPP

#include <QCheckBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFontDatabase>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QSpinBox>
#include <QStackedWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "dialog.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

class Settings : public Dialog
{
    Q_OBJECT
private:
    QStackedWidget *stack;
    QListWidget *list;
private:
    void createApktoolTab();
    void createEditorTab();
    void createGeneralTab();
    void createJavaTab();
    void createViewerTab();
    void fixButtonSize(QPushButton *);
    static QString translate(const char *key) {
        return Helpers::Text::translate("settings", key);
    }
public:
    explicit Settings(QWidget * = 0);
};

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WINDOWS_SETTINGS_HPP
