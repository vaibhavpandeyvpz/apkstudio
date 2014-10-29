#ifndef VPZ_APKSTUDIO_COMPONENTS_OUTPUT_HPP
#define VPZ_APKSTUDIO_COMPONENTS_OUTPUT_HPP

#include <QDockWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include "helpers/adb.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "terminal.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Output : public QDockWidget
{
    Q_OBJECT
private:
    QTextEdit *apk_studio;
    QTextEdit *apk_tool;
    QList<QMetaObject::Connection> connections;
    QTabWidget *tabs;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("output", key);
    }
    void createADBTab();
    void createAPKStudioTab();
    void createAPKToolTab();
public:
    explicit Output(QWidget *parent = 0);
    ~Output();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_OUTPUT_HPP
