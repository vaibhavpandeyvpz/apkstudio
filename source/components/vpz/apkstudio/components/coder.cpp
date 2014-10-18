#include "coder.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Coder::Coder(QWidget *parent) :
    QPlainTextEdit(parent)
{
    QStringList required;
    required << "background" << "foreground" << "highlight" << "selection";
    QList<Resources::Style> styles = Application::theme();
    foreach (Resources::Style style, styles) {
        if (!required.contains(style.name))
            continue;
        theme.insert(style.name, style.color);
    }
    QFont font;
    font.setFamily(Settings::fontFamily());
    font.setFixedPitch(true);
    font.setPointSize(Settings::fontSize());
    font.setStyleHint(QFont::Monospace);
    QFontMetrics metrics(font);
    QPalette palette;
    palette.setColor(QPalette::Highlight, QColor(theme.value("selection")));
    palette.setColor(QPalette::HighlightedText, QColor("#FFFFFF"));
    palette.setColor(QPalette::Active, QPalette::Base, QColor(theme.value("background")));
    palette.setColor(QPalette::Inactive, QPalette::Base, QColor(theme.value("background")));
    palette.setColor(QPalette::Text, QColor(theme.value("foreground")));
    highlightCurrentLine();
    setFont(font);
    setFrameStyle(QFrame::NoFrame);
    setPalette(palette);
    setTabStopWidth(Settings::tabWidth() * metrics.width(' '));
    setWordWrapMode(Settings::wordWrap() ? QTextOption::WordWrap : QTextOption::NoWrap);
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
}

void Coder::highlightCurrentLine()
{
    // Update
    QTextCursor cursor = this->textCursor();
    /* int line = cursor.blockNumber() + 1;
    int column = cursor.columnNumber() + 1;
    emit changed(line, column); */
    // Completion
    QList<QTextEdit::ExtraSelection> selections;
    if (isReadOnly()) {
        setExtraSelections(selections);
        return;
    }
    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(QColor(theme.value("highlight")));
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    selection.cursor.clearSelection();
    selections.append(selection);
    setExtraSelections(selections);
}

void Coder::keyPressEvent(QKeyEvent *event)
{
    bool backward = false;
    bool override = false;
    QString text = event->text();
    switch (event->key()) {
    case Qt::Key_Apostrophe: {
        backward = true;
        override = true;
        text = "''";
        break;
    }
    case Qt::Key_Backtab:
        if (false) {
            event->ignore();
            return;
        }
        break;
    case Qt::Key_BraceLeft: {
        backward = true;
        override = true;
        text = "{}";
        break;
    }
    case Qt::Key_BracketLeft: {
        backward = true;
        override = true;
        text = "[]";
        break;
    }
    case Qt::Key_Enter:
        if (false) {
            event->ignore();
            return;
        }
        break;
    case Qt::Key_Escape:
        if (false) {
            event->ignore();
            return;
        }
        break;
    case Qt::Key_ParenLeft: {
        backward = true;
        override = true;
        text = "()";
        break;
    }
    case Qt::Key_QuoteDbl: {
        backward = true;
        override = true;
        text = "\"\"";
        break;
    }
    case Qt::Key_Return:
        if (false) {
            event->ignore();
            return;
        } /* else {
            override = true;
            QTextCursor cursor = this->textCursor();
            QString line = cursor.block().text();
            QString whitespace = line.replace(QString("[^\\s+]*"), QString(""));
            cursor.movePosition(QTextCursor::Left);
            cursor.movePosition(QTextCursor::EndOfWord);
            cursor.insertText(QString("\n").append(whitespace).append("    "));
            return;
        } */
        break;
    case Qt::Key_Tab:
        if (false) {
            event->ignore();
            return;
        } else if (Settings::spacesForTab()) {
            override = true;
            text = "    ";
        }
        break;
    default:
        break;
    }
    if (override) {
        QTextCursor cursor = textCursor();
        cursor.insertText(text);
        if (backward)
            cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        setTextCursor(cursor);
        return;
    }
    bool shortcut = ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_Space);
    if (!shortcut)
        QPlainTextEdit::keyPressEvent(event);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
