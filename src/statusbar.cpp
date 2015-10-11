#include "include/adb.h"
#include "include/apktool.h"
#include "include/java.h"
#include "include/statusbar.h"
#include "include/qrc.h"

APP_NAMESPACE_START

StatusBar::StatusBar(QWidget *parent)
    : QStatusBar(parent)
{
    QLabel *adb;
    QLabel *apkTool;
    QLabel *java;
    addPermanentWidget(java = new QLabel(this));
    addPermanentWidget(new StatusBarSeparator(this));
    addPermanentWidget(adb = new QLabel(this));
    addPermanentWidget(new StatusBarSeparator(this));
    addPermanentWidget(apkTool = new QLabel(this));
    addPermanentWidget(new QWidget(this), 1);
    addPermanentWidget(_message = new QLabel(this));
    setContentsMargins(4, 0, 4, 0);
    setStyleSheet("QStatusBar::item { border: none; }");
    QString v;
    if ((v = Adb::get()->getVersion()).isEmpty() == false)
    {
        adb->setText(__("version_adb", "statusbar", v));
    }
    else
    {
        adb->setText(__("version_adb", "statusbar", "n/a"));
    }
    if ((v = ApkTool::get()->getVersion()).isEmpty() == false)
    {
        apkTool->setText(__("version_apktool", "statusbar", v));
    }
    else
    {
        apkTool->setText(__("version_apktool", "statusbar", "n/a"));
    }
    if ((v = Java::get()->getVersion()).isEmpty() == false)
    {
        java->setText(__("version_java", "statusbar", v));
    }
    else
    {
        java->setText(__("version_java", "statusbar", "n/a"));
    }
    _connections << connect(this, &QStatusBar::messageChanged, this, &StatusBar::onMessageChanged);
    _message->setText(__("ready", "statusbar"));
}

void StatusBar::onMessageChanged(const QString &text)
{
    _message->setText(text);
}

StatusBar::~StatusBar()
{
    APP_CONNECTIONS_DISCONNECT
}

StatusBarSeparator::StatusBarSeparator(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::VLine);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
}

APP_NAMESPACE_END
