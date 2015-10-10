#include <QApplication>
#include <QFontDatabase>
#include <QProcess>
#include <QStyleFactory>
#include <QTimer>
#include <QTranslator>
#include "constants.h"
#include "ide.h"
#include "fileutils.h"
#include "process.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<APP_NAMESPACE::Process::Result>("Result");
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setOrganizationName(APP_ORGANIZATION);
    QFontDatabase::addApplicationFont(QString(QRC_FONTS).append("scp_regular.ttf"));
    QFontDatabase::addApplicationFont(QString(QRC_FONTS).append("scp_bold.ttf"));
    QApplication app(argc, argv);
#ifdef Q_OS_WIN
    // app.setStyle(QStyleFactory::create("fusion"));
#endif
    QTranslator translator;
    translator.load("en", QRC_LANG);
    app.installTranslator(&translator);
    app.setStyleSheet(APP_NAMESPACE::FileUtils::read(QString(QRC_STYLES).arg("default")));
    APP_NAMESPACE::Ide ide;
    ide.show();
    QTimer::singleShot(0, &ide, &APP_NAMESPACE::Ide::onInit);
    return app.exec();
}
