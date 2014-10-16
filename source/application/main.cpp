#include <QApplication>
#include <QFontDatabase>
#include <QTimer>
#include <QTranslator>
#include "helpers/settings.hpp"
#include "resources/constant.hpp"
#include "resources/embedded.hpp"
#include "windows/ide.hpp"

using namespace VPZ::APKStudio::Helpers;
using namespace VPZ::APKStudio::Resources;
using namespace VPZ::APKStudio::Windows;

int main(int count, char *arguments[])
{
    // Settings
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setOrganizationName(APPLICATION_AUTHOR);
    int code = 0;
    do {
        // Application
        QApplication qtApp(count, arguments);
        qtApp.setWindowIcon(Embedded::icon("apkstudio"));
        // Fonts
        QFontDatabase::addApplicationFont(QString(RESOURCE_PATH_FONT).append("scpro_regular.ttf"));
        QFontDatabase::addApplicationFont(QString(RESOURCE_PATH_FONT).append("scpro_bold.ttf"));
        // Translator
        QTranslator translator;
        translator.load(Settings::language(), RESOURCE_PATH_LANGUAGE);
        qtApp.installTranslator(&translator);
        // IDE
        IDE ide;
        ide.show();
        QTimer::singleShot(0, &ide, SLOT(onInitComplete()));
        // Run
        code = qtApp.exec();
    } while (code == EXIT_CODE_RESTART);
    return code;
}
