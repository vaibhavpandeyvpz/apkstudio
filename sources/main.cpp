#include <QApplication>
#include <QSettings>
#include "splashwindow.h"
#include "../Qt-Frameless-Window-DarkStyle/DarkStyle.h"

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
            app.setStyle(new DarkStyle);
        }
        SplashWindow window;
        window.show();
        code = app.exec();
    } while (code == CODE_RESTART);
    return code;
}
