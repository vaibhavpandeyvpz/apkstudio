#include "splashwindow.h"
#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QTextStream>

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
        QFile qss(":/qdarkstyle/style.qss");
        if (qss.exists() && qss.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream styles(&qss);
            app.setStyleSheet(styles.readAll());
            qss.close();
        }
    }
    SplashWindow window;
    window.show();
    return app.exec();
}
