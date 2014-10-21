#include "coder.hpp"
#include <QDebug>

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Coder::Coder(QWidget *parent) :
    QPlainTextEdit(parent), line_numbers(new LineNumbers(this)), theme(Application::theme())
{
    bracket_matcher = new BracketMatcher(this, theme.value("bracket").color);
    QFont font;
    font.setFamily(Settings::fontFamily());
    font.setFixedPitch(true);
    font.setPointSize(Settings::fontSize());
    font.setStyleHint(QFont::Monospace);
    QFontMetrics metrics(font);
    QPalette palette;
    palette.setColor(QPalette::Highlight, QColor(theme.value("selection").color));
    palette.setColor(QPalette::HighlightedText, QColor(theme.value("selected").color));
    palette.setColor(QPalette::Active, QPalette::Base, QColor(theme.value("background").color));
    palette.setColor(QPalette::Inactive, QPalette::Base, QColor(theme.value("background").color));
    palette.setColor(QPalette::Text, QColor(theme.value("foreground").color));
    setFont(font);
    setFrameStyle(QFrame::NoFrame);
    setPalette(palette);
    setTabStopWidth(Settings::tabWidth() * metrics.width(' '));
    setWordWrapMode(Settings::wordWrap() ? QTextOption::WordWrap : QTextOption::NoWrap);
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChanged()));
    connect(this, SIGNAL(blockCountChanged(const int)), this, SLOT(onBlockCountChanged(const int)));
    connect(this, SIGNAL(updateRequest(const QRect &, const int)), this, SLOT(onUpdateRequest(const QRect, const int)));
    onBlockCountChanged(0);
    onCursorPositionChanged();
}

bool Coder::event(QEvent *event)
{
    if (event->type() != QEvent::ToolTip)
        return QPlainTextEdit::event(event);
    QHelpEvent *help = static_cast<QHelpEvent *>(event);
    QTextCursor cursor = cursorForPosition(help->pos());
    cursor.select(QTextCursor::WordUnderCursor);
    if (!cursor.selectedText().isEmpty()) {
        QToolTip::hideText();
        return true;
    }
    QToolTip::showText(help->globalPos(), cursor.selectedText());
    return true;
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
        }
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

int Coder::lineNumbersAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    digits++;
    digits++;
    return (3 + fontMetrics().width('9') * digits);
}

void Coder::lineNumbersPaintEvent(QPaintEvent *event)
{
    QPainter painter(line_numbers);
    painter.fillRect(event->rect(), theme.value("lines").color);
    QTextBlock block = firstVisibleBlock();
    int number = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    while (block.isValid() && (top <= event->rect().bottom())) {
        if (block.isVisible() && (bottom >= event->rect().top())) {
            QString newer = QString::number(number + 1).append(" ");
            painter.setPen(QColor(theme.value("line").color));
            painter.drawText(0, top, line_numbers->width(), fontMetrics().height(), Qt::AlignRight, newer);
        }
        block = block.next();
        top = bottom;
        bottom = (top + ((int) blockBoundingRect(block).height()));
        ++number;
    }
}

void Coder::onBlockCountChanged(const int /* count */)
{
    setViewportMargins(lineNumbersAreaWidth(), 0, 0, 0);
}

void Coder::onCursorPositionChanged()
{
    /* QTextCursor cursor = this->textCursor();
    int line = cursor.blockNumber() + 1;
    int column = cursor.columnNumber() + 1;
    emit changed(line, column); */
    QList<QTextEdit::ExtraSelection> selections;
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(QColor(theme.value("highlight").color));
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        selections.append(selection);
        setExtraSelections(selections);
    }
    foreach (QString pair, Settings::brackets())
        bracket_matcher->match(pair[0], pair[1]);
}

void Coder::onUpdateRequest(const QRect &rectangle, const int column)
{
    if (column)
        line_numbers->scroll(0, column);
    else if ((cache.first != blockCount()) || (cache.second != textCursor().block().lineCount())) {
        line_numbers->update(0, rectangle.y(), line_numbers->width(), rectangle.height());
        cache.first = blockCount();
        cache.second = textCursor().block().lineCount();
    }
    if (rectangle.contains(viewport()->rect()))
        onBlockCountChanged(0);
}

void Coder::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    QRect resized = contentsRect();
    line_numbers->setGeometry(QRect(resized.left(), resized.top(), lineNumbersAreaWidth(), resized.height()));
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
