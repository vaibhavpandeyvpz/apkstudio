#include <QApplication>
#include <QSettings>
#include <QTextStream>
#include <QDateTime>
#include "darkstyle.h"
#include "lightstyle.h"
#include "splashwindow.h"

#define CODE_RESTART 60600

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString typeStr;
    switch (type) {
    case QtDebugMsg:
        typeStr = "DEBUG";
        break;
    case QtInfoMsg:
        typeStr = "INFO";
        break;
    case QtWarningMsg:
        typeStr = "WARNING";
        break;
    case QtCriticalMsg:
        typeStr = "CRITICAL";
        break;
    case QtFatalMsg:
        typeStr = "FATAL";
        break;
    }
    cout << QString("[%1] [%2] %3").arg(timestamp, typeStr, msg) << Qt::endl;
    cout.flush();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    
    QApplication::setApplicationName("APK Studio");
    QApplication::setOrganizationDomain("vaibhavpandey.com");
    QApplication::setOrganizationName("Vaibhav Pandey");
    int code = 0;
    do {
        QApplication app(argc, argv);
        app.setWindowIcon(QIcon(":/images/icon.png"));

        QSettings settings;
        const bool dark = settings.value("dark_theme", false).toBool();
        if (dark) {
            app.setStyle(new DarkStyle());
        } else {
            app.setStyle(new LightStyle());
        }

        SplashWindow window;
        window.show();
        code = app.exec();
    } while (code == CODE_RESTART);
    return code;
}
