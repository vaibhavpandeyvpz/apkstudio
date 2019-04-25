#include <QApplication>
#include <QSettings>
#include "splashwindow.h"
#include "../Qt-Frameless-Window-DarkStyle/DarkStyle.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("APK Studio");
    QCoreApplication::setOrganizationDomain("vaibhavpandey.com");
    QCoreApplication::setOrganizationName("Vaibhav Pandey");
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/icon.png"));
    QSettings settings;
    const bool dark = settings.value("dark_theme", false).toBool();
    if (dark) {
        app.setStyle(new DarkStyle);
    }
    SplashWindow window;
    window.show();
    return app.exec();
}
