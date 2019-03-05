#include "splashwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("APK Studio");
    QCoreApplication::setOrganizationDomain("vaibhavpandey.com");
    QCoreApplication::setOrganizationName("Vaibhav Pandey");
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/icon.png"));
    SplashWindow window;
    window.show();
    return app.exec();
}
