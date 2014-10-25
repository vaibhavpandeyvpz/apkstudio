#include "coder.hpp"
#include "linenumbers.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Coder::Coder(QWidget *parent) :
    QPlainTextEdit(parent), brackets_matcher(new BracketMatcher(this)), highlighter(new Helpers::Highlighter(this)), line_numbers(new LineNumbers(this)), theme(Application::theme())
{
    QMenu *context_menu = new QMenu(this);
    brackets_matcher->background(theme.value("bracket").color);
    highlighter->setDocument(document());
    line_numbers->background(QColor(theme.value("lines").color));
    line_numbers->foreground(QColor(theme.value("line").color));
    QFont font;
    font.setFamily(Settings::fontFamily());
    font.setFixedPitch(true);
    font.setPointSize(Settings::fontSize());
    font.setStyleHint(QFont::TypeWriter);
    QFontMetrics metrics(font);
    QPalette palette;
    palette.setColor(QPalette::Highlight, QColor(theme.value("selection").color));
    palette.setColor(QPalette::HighlightedText, QColor(theme.value("selected").color));
    palette.setColor(QPalette::Active, QPalette::Base, QColor(theme.value("background").color));
    palette.setColor(QPalette::Inactive, QPalette::Base, QColor(theme.value("background").color));
    palette.setColor(QPalette::Text, QColor(theme.value("foreground").color));
    setCursorWidth(Settings::cursorWidth());
    setFont(font);
    setFrameStyle(QFrame::NoFrame);
    setPalette(palette);
    setTabChangesFocus(false);
    setTabStopWidth(Settings::tabWidth() * metrics.width('8'));
    setWordWrapMode(Settings::wordWrap() ? QTextOption::WordWrap : QTextOption::NoWrap);
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChanged()));
    connections.append(connect(this, &Coder::customContextMenuRequested, [this, context_menu] (const QPoint &position) {
        context_menu->popup(this->viewport()->mapToGlobal(position));
    }));
    connect(this, SIGNAL(blockCountChanged(const int)), this, SLOT(onBlockCountChanged(const int)));
    connect(this, SIGNAL(updateRequest(const QRect &, const int)), this, SLOT(onUpdateRequest(const QRect, const int)));
    onBlockCountChanged(0);
    onCursorPositionChanged();
    QTextOption options = document()->defaultTextOption();
    if (Settings::showWhitespace())
        options.setFlags(options.flags() | QTextOption::ShowTabsAndSpaces);
    else
        options.setFlags(options.flags() & ~QTextOption::ShowTabsAndSpaces);
    options.setFlags(options.flags());
    document()->setDefaultTextOption(options);
}

bool Coder::event(QEvent *event)
{
    if ((event->type() == QEvent::KeyPress)) {
        QKeyEvent *keyevent = (QKeyEvent*) event;
        if (keyevent->key() == Qt::Key_Tab) {
            if (indent())
                return true;
            QString text = Settings::spacesForTab() ? QString(Settings::tabWidth(), ' ') : "\t";
            QTextCursor cursor = textCursor();
            cursor.insertText(text);
            setTextCursor(cursor);
            return true;
        }
    } else if (event->type() == QEvent::ToolTip) {
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
    return QPlainTextEdit::event(event);
}

bool Coder::indent()
{
    QTextCursor cursor = textCursor();
    if (!cursor.hasSelection())
        return false;
    int start = cursor.anchor();
    int stop = cursor.position();
    if (start > stop)
        std::swap(start, stop);
    cursor.setPosition(start, QTextCursor::MoveAnchor);
    int begin = cursor.block().blockNumber();
    cursor.setPosition(stop, QTextCursor::MoveAnchor);
    int end = cursor.block().blockNumber();
    cursor.setPosition(start, QTextCursor::MoveAnchor);
    cursor.beginEditBlock();
    const int difference = (end - begin);
    for (int i = 0; i <= difference; ++i) {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.insertText(Settings::spacesForTab() ? QString(Settings::tabWidth(), ' ') : "\t");
        cursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
    }
    cursor.endEditBlock();
    cursor.setPosition(start, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
    while (cursor.block().blockNumber() < end)
        cursor.movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    setTextCursor(cursor);
    return true;
}

void Coder::keyPressEvent(QKeyEvent *event)
{
    bool replace = true;
    QString text = event->text();
    switch (event->key()) {
    case Qt::Key_Backtab:
    case Qt::Key_Enter:
    case Qt::Key_Escape:
    case Qt::Key_Return: {
        if (false) {
            event->ignore();
            return;
        }
        replace = false;
        break;
    }
    case Qt::Key_Apostrophe: {
        text = "''";
        break;
    }
    case Qt::Key_BraceLeft: {
        text = "{}";
        break;
    }
    case Qt::Key_BracketLeft: {
        text = "[]";
        break;
    }
    case Qt::Key_ParenLeft: {
        text = "()";
        break;
    }
    case Qt::Key_QuoteDbl: {
        text = "\"\"";
        break;
    }
    default:
        replace = false;
        break;
    }
    if (replace) {
        QTextCursor cursor = textCursor();
        cursor.insertText(text);
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        setTextCursor(cursor);
        event->ignore();
        return;
    }
    bool shortcut = ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_Space);
    if (!shortcut && event->isAccepted())
        QPlainTextEdit::keyPressEvent(event);
}

void Coder::onBlockCountChanged(const int /* count */)
{
    setViewportMargins(line_numbers->sizeHint().width(), 0, 0, 0);
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
        brackets_matcher->match(pair[0], pair[1]);
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

void Coder::paintEvent(QPaintEvent *event)
{
    QPlainTextEdit::paintEvent(event);
    if (!Settings::showWhitespace())
        return;
    QPainter painter(viewport());
    int width = fontMetrics().width("\u00B6");
    int height = fontMetrics().height();
    QTextBlock block = firstVisibleBlock();
    while (block.isValid()) {
        QRectF geometry = blockBoundingGeometry(block).translated(contentOffset());
        if (geometry.top() > event->rect().bottom())
            break;
        if (block.isVisible() && geometry.toRect().intersects(event->rect())) {
            QString text = block.text().replace("\t", QString(Settings::tabWidth(), '8')).append(' ');
            painter.setPen(QColor(theme.value("whitespace").color));
            painter.drawText(geometry.left() + fontMetrics().width(text), geometry.top(), width, height, Qt::AlignLeft | Qt::AlignVCenter, "\u00B6");
        }
        block = block.next();
    }
}

void Coder::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    QRect resized = contentsRect();
    line_numbers->setGeometry(QRect(resized.left(), resized.top(), line_numbers->sizeHint().width(), resized.height()));
}

void Coder::setFont(const QFont &font)
{
    QPlainTextEdit::setFont(font);
    line_numbers->setFont(font);
}

Coder::~Coder()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
