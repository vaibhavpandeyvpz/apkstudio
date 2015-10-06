#include "adb.h"
#include "apktool.h"
#include "java.h"
#include "statusbar.h"
#include "qrc.h"

AS_NAMESPACE_START

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
        adb->setText(QString("ADB: %1").arg(v));
    }
    else
    {
        adb->setText(QString("ADB: %1").arg(Qrc::text("statusbar.version.unknown")));
    }
    if ((v = ApkTool::get()->getVersion()).isEmpty() == false)
    {
        apkTool->setText(QString("APK Tool: %1").arg(v));
    }
    else
    {
        apkTool->setText(QString("APK Tool: %1").arg(Qrc::text("statusbar.version.unknown")));
    }
    if ((v = Java::get()->getVersion()).isEmpty() == false)
    {
        java->setText(QString("Java: %1").arg(v));
    }
    else
    {
        java->setText(QString("Java: %1").arg(Qrc::text("statusbar.version.unknown")));
    }
    _connections << connect(this, QStatusBar::messageChanged, this, StatusBar::onMessageChanged);
    _message->setText(Qrc::text("statusbar.message.ready"));
}

void StatusBar::onMessageChanged(const QString &text)
{
    _message->setText(text);
}

StatusBar::~StatusBar()
{
    AS_CONNECTIONS_DISCONNECT
}

StatusBarSeparator::StatusBarSeparator(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::VLine);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
}

AS_NAMESPACE_END
