#include <QLayout>
#include "include/adb.h"
#include "include/apktool.h"
#include "include/consoledock.h"
#include "include/constants.h"
#include "include/uberapksigner.h"
#include "include/qrc.h"

APP_NAMESPACE_START

ConsoleDock::ConsoleDock(QWidget *parent)
    : QDockWidget(__("console", "docks"), parent)
{
    _edit = new QTextEdit(this);
    QFont font;
    font.setFamily("Courier New");
    font.setFixedPitch(true);
    font.setPointSize(9);
    font.setStyleHint(QFont::TypeWriter);
    QFontMetrics metrics(font);
    QPalette palette;
    palette.setColor(QPalette::Active, QPalette::Base, QColor("#000000"));
    palette.setColor(QPalette::Inactive, QPalette::Base, QColor("#000000"));
    _edit->setFont(font);
    _edit->setFrameStyle(QFrame::NoFrame);
    _edit->setPalette(palette);
    _edit->setReadOnly(true);
    _edit->setTabStopWidth(4 * metrics.width('8'));
    _edit->setWordWrapMode(QTextOption::NoWrap);
    setContentsMargins(2, 2, 2, 2);
    setObjectName("ConsoleDock");
    setWidget(_edit);
    _connections << connect(Adb::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(Adb::get(), &Process::executing, this, &ConsoleDock::onExecuting);
    _connections << connect(ApkTool::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(ApkTool::get(), &Process::executing, this, &ConsoleDock::onExecuting);
    _connections << connect(UberApkSigner::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(UberApkSigner::get(), &Process::executing, this, &ConsoleDock::onExecuting);
    _connections << connect(Java::get(), &Process::executed, this, &ConsoleDock::onExecuted);
    _connections << connect(Java::get(), &Process::executing, this, &ConsoleDock::onExecuting);

}

void ConsoleDock::onExecuted(const Process::Result &r)
{
    if (!r.error.isEmpty())
    {
        _edit->setTextColor(QColor(COLOR_ERROR));
        foreach (const QString &l, r.error)
        {
            _edit->append(l);
        }
    }
    if (!r.output.isEmpty())
    {
        _edit->setTextColor(QColor(COLOR_OUTPUT));
        foreach (const QString &l, r.output)
        {
            _edit->append(l);
        }
    }
    _edit->setTextColor(QColor(COLOR_CODE));
    _edit->append(__("exit_code", "console", QString::number(r.code)));
    _edit->append(QString());
}

void ConsoleDock::onExecuting(const QString &c, const QStringList &a)
{
    QString line = "$ " + c;
    foreach (const QString &i, a)
    {
        QString arg(i);
        if (i.contains(' '))
        {
            arg.prepend('\"');
            arg.append('\"');
        }
        line.append(' ' + arg);
    }
    _edit->setTextColor(QColor(COLOR_COMMAND));
    _edit->append(line.trimmed());
}

ConsoleDock::~ConsoleDock()
{
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
