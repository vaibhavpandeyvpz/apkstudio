#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QProcess>
#include <QStyleFactory>
#include <QTimer>
#include <QTranslator>
#include "include/constants.h"
#include "include/ide.h"
#include "include/fileutils.h"
#include "include/process.h"

using namespace APP_NAMESPACE;

int main(int argc, char *argv[])
{
    qRegisterMetaType<Process::Result>("Result");
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setOrganizationName(APP_ORGANIZATION);
    QFontDatabase::addApplicationFont(QString(QRC_FONTS).append("scp_regular.ttf"));
    QFontDatabase::addApplicationFont(QString(QRC_FONTS).append("scp_bold.ttf"));
    QApplication app(argc, argv);
    QTranslator translator;
    translator.load("en", QRC_LANG);
    app.installTranslator(&translator);
    app.setStyleSheet(FileUtils::read(QString(QRC_STYLES).arg("default")));
    Ide ide;
    ide.show();
    QTimer::singleShot(0, &ide, SLOT(onInit()));
    return app.exec();
}
