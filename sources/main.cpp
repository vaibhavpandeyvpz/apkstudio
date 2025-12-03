#include <QApplication>
#include <QSettings>
#include "darkstyle.h"
#include "lightstyle.h"
#include "splashwindow.h"

#define CODE_RESTART 60600

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("APK Studio");
    QApplication::setOrganizationDomain("vaibhavpandey.com");
    QApplication::setOrganizationName("Vaibhav Pandey");
    int code = 0;
    do {
        QApplication app(argc, argv);
        app.setWindowIcon(QIcon(":/images/icon.png"));

        QSettings settings;
        const bool dark = settings.value("dark_theme", false).toBool();
        if (dark) {
            app.setStyle(new DarkStyle());
        } else {
            app.setStyle(new LightStyle());
        }

        SplashWindow window;
        window.show();
        code = app.exec();
    } while (code == CODE_RESTART);
    return code;
}
