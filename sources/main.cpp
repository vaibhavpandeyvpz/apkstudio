#include "splashwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SplashWindow window;
    window.show();
    return app.exec();
}
