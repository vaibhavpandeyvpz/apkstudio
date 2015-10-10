#include <QLayout>
#include "consoledock.h"
#include "constants.h"
#include "qrc.h"

APP_NAMESPACE_START

ConsoleDock::ConsoleDock(const QString &title, const QString &binary, QWidget *parent)
    : QDockWidget(title, parent), _binary(binary)
{
    setContentsMargins(2, 2, 2, 2);
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
    setWidget(_edit);
}

void ConsoleDock::onExecuted(const Process::Result &r)
{
    if (!r.error.isEmpty())
    {
        _edit->setTextColor(QColor(COLOR_ERROR));
        for (const QString &l : r.error)
        {
            _edit->append(l);
        }
    }
    if (!r.output.isEmpty())
    {
        _edit->setTextColor(QColor(COLOR_OUTPUT));
        for (const QString &l : r.output)
        {
            _edit->append(l);
        }
    }
    _edit->setTextColor(QColor(COLOR_CODE));
    _edit->append(QString(Qrc::text("dock.console.exit_code")).arg(r.code));
    _edit->append(QString());
}

void ConsoleDock::onExecuting(const QStringList &cs)
{
    QString line = QString("$ %1 ")
#ifdef Q_OS_WIN
            .arg(_binary + ".exe");
#else
            .arg(_binary);
#endif
    foreach (const QString &c, cs)
    {
        if (c.contains(' '))
        {
            line.append('\"');
        }
        line.append(c);
        if (c.contains(' '))
        {
            line.append('\"');
        }
        line.append(' ');
    }
    _edit->setTextColor(QColor(COLOR_COMMAND));
    _edit->append(line.trimmed());
}

ConsoleDock::~ConsoleDock()
{
    AS_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
