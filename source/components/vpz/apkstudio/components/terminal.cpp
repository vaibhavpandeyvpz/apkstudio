#include "terminal.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Terminal::Terminal(const QString &binary, QWidget *parent) :
    QTextEdit(parent), binary(binary), command(QColor("#39B54A")), output(QColor("#FFFFFF"))
{
    QFont font;
    font.setFamily("Terminus (TTF)");
    font.setFixedPitch(true);
    font.setPointSize(11);
    font.setStyleHint(QFont::TypeWriter);
    QFontMetrics metrics(font);
    QPalette palette;
    palette.setColor(QPalette::Active, QPalette::Base, QColor("#000000"));
    palette.setColor(QPalette::Inactive, QPalette::Base, QColor("#000000"));
    palette.setColor(QPalette::Text, output);
    setFont(font);
    setFrameStyle(QFrame::NoFrame);
    setPalette(palette);
    setReadOnly(true);
    setTabStopWidth(4 * metrics.width('8'));
}

void Terminal::onCommandExecuted(const QStringList &arguments, const QStringList &output)
{
    QString command = QString("$ %1").arg(binary);
    bool whitespace = false;
    foreach (const QString &argument, arguments) {
        command.append(' ');
        whitespace = argument.contains(' ');
        if (whitespace)
            command.append('\"');
        command.append(argument);
        if (whitespace)
            command.append('\"');
    }
    setTextColor(this->command);
    append(command);
    setTextColor(this->output);
    append(output.join("\n").append("\n"));
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
