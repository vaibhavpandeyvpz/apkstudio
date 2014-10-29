#include <QApplication>
#include <QFontDatabase>
#include <QStyleFactory>
#include <QTimer>
#include <QTranslator>
#include "helpers/application.hpp"
#include "helpers/settings.hpp"
#include "resources/constant.hpp"
#include "resources/embedded.hpp"
#include "windows/ide.hpp"

using namespace VPZ::APKStudio;

int main(int count, char *arguments[])
{
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setOrganizationName(APPLICATION_AUTHOR);
    int code = 0;
    do {
        QString theme(Helpers::Settings::theme());
        Helpers::Application qtApp(count, arguments);
        qtApp.setWindowIcon(Resources::Embedded::icon("apkstudio"));
        if ((QString::compare(theme, "default", Qt::CaseInsensitive) != 0)) {
            qtApp.setStyle(QStyleFactory::create("fusion"));
            if ((QString::compare(theme, "dark", Qt::CaseInsensitive) == 0)) {
                QPalette palette;
                palette.setColor(QPalette::Window, QColor(53,53,53));
                palette.setColor(QPalette::WindowText, Qt::white);
                palette.setColor(QPalette::Base, QColor(25,25,25));
                palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
                palette.setColor(QPalette::ToolTipBase, Qt::white);
                palette.setColor(QPalette::ToolTipText, Qt::white);
                palette.setColor(QPalette::Text, Qt::white);
                palette.setColor(QPalette::Button, QColor(53,53,53));
                palette.setColor(QPalette::ButtonText, Qt::white);
                palette.setColor(QPalette::BrightText, Qt::red);
                palette.setColor(QPalette::Link, QColor(42, 130, 218));
                palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
                palette.setColor(QPalette::HighlightedText, Qt::black);
                qtApp.setPalette(palette);
                qtApp.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
            }
        }
        QFontDatabase::addApplicationFont(QString(RESOURCE_PATH_FONT).append("droid_sans_mono.ttf"));
        QFontDatabase::addApplicationFont(QString(RESOURCE_PATH_FONT).append("scpro_regular.ttf"));
        QFontDatabase::addApplicationFont(QString(RESOURCE_PATH_FONT).append("scpro_bold.ttf"));
        QFontDatabase::addApplicationFont(QString(RESOURCE_PATH_FONT).append("terminus_ttf.ttf"));
        QTranslator translator;
        translator.load(Helpers::Settings::language(), RESOURCE_PATH_LANGUAGE);
        qtApp.installTranslator(&translator);
        Windows::IDE ide;
        ide.show();
        QTimer::singleShot(0, &ide, SLOT(onInitComplete()));
        code = qtApp.exec();
    } while (code == EXIT_CODE_RESTART);
    return code;
}
