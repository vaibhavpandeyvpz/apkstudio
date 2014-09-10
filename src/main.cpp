#include <QApplication>
#include <QFontDatabase>
#include <QTimer>
#include <QTranslator>

#include "constant.h"
#include "ide.h"

int main(int count, char *arguments[])
{
    // Settings
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setOrganizationName(APPLICATION_AUTHOR);
    // Fonts
    QFontDatabase::addApplicationFont(QString(RESOURCE_PATH_FONT).append("scpro-regular.ttf"));
    QFontDatabase::addApplicationFont(QString(RESOURCE_PATH_FONT).append("scpro-bold.ttf"));
    int code = 0;
    do {
        // Application
        QApplication qtApp(count, arguments);
        qtApp.setWindowIcon(Utility::icon("apkstudio"));
        // Translator
        QTranslator translator;
        translator.load(Settings::language(), RESOURCE_PATH_LANGUAGE);
        qtApp.installTranslator(&translator);
        // IDE
        IDE ide;
        ide.show();
        QTimer::singleShot(0, &ide, SLOT(inflate()));
        // Run
        code = qtApp.exec();
    } while (code == EXIT_CODE_RESTART);
    return code;
}
