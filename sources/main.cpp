#include "splashwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/icon.png"));
    SplashWindow window;
    window.show();
    return app.exec();
}
