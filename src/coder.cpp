#include <QAbstractItemView>
#include <QApplication>
#include <QMimeData>
#include <QPainter>
#include <QScrollBar>
#include <QShortcut>
#include <QToolTip>
#include "include/coder.h"
#include "include/codersidebar.h"
#include "include/fileutils.h"
#include "include/preferences.h"

APP_NAMESPACE_START

Coder::Coder(QWidget *parent) :
    QPlainTextEdit(parent)
{
    _connections << connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(onUpdateMargins(int)));
    _connections << connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChanged()));
    _connections << connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(onUpdateRequest(QRect, int)));
    _connections << connect(new QShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_U, this), SIGNAL(activated()), this, SLOT(onTransformToLower()));
    _connections << connect(new QShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_Up, this), SIGNAL(activated()), this, SLOT(onMoveLineUp()));
    _connections << connect(new QShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_Down, this), SIGNAL(activated()), this, SLOT(onMoveLineDown()));
    _connections << connect(new QShortcut(Qt::CTRL | Qt::Key_U, this), SIGNAL(activated()), this, SLOT(onTransformToUpper()));
    _sidebar = new CoderSidebar(this);
    Preferences *pr = Preferences::get();
    _spacesForTabs = pr->useSpacesForTabs();
    setCursorWidth(2);
    if(pr->showWhitespaces())
    {
        QTextOption o;
        o.setFlags(QTextOption::ShowTabsAndSpaces);
        document()->setDefaultTextOption(o);
    }
    QFont f("Source Code Pro");
    setFont(f);
    setFrameStyle(QFrame::NoFrame);
    setTabChangesFocus(false);
    setTabStopWidth(pr->tabStopWidth());
    setWordWrapMode(QTextOption::NoWrap);
    QTimer::singleShot(0, this, SLOT(onInit()));
}

QString Coder::addIndent(QString text, int count)
{
    if (text.isEmpty())
    { return text; }
    while ((text.at(0) == ' ') || (text.at(0) == '\t'))
    {
        text.remove(0, 1);
        if (text.isEmpty())
        { break; }
    }
    while (count != 0)
    {
        text = text.insert(0, _spacesForTabs ? QString(_tabStopWidth, ' ') : QChar('\t'));
        count--;
    }
    return text;
}

QTextCursor Coder::currentTextCursor() const
{
    QTextCursor c = textCursor();
    if (!c.hasSelection())
    { c.select(QTextCursor::WordUnderCursor); }
    return c;
}

int Coder::currentColumn() const
{
    QTextCursor c = textCursor();
    return c.position() - c.block().position() + 1;
}

int Coder::currentRow() const
{
    return textCursor().blockNumber() + 1;
}

void Coder::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    { event->acceptProposedAction(); }
    else
    { QPlainTextEdit::dragEnterEvent(event); }
}

void Coder::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasUrls())
    { event->acceptProposedAction(); }
    else
    { QPlainTextEdit::dragMoveEvent(event); }
}

void Coder::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
        emit fileDropped(event->mimeData()->urls().at(0).toLocalFile());
    }
    else
    { QPlainTextEdit::dropEvent(event); }
}

bool Coder::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ToolTip:
    {
        QHelpEvent *help = static_cast<QHelpEvent*>(event);
        if (QApplication::keyboardModifiers() & Qt::ControlModifier)
        { return true; }
        emit tooltipRequested(help->pos());
        return true;
    }
    default:
        break;
    }
    return QPlainTextEdit::event(event);
}

void Coder::focusInEvent(QFocusEvent *event)
{
    QPlainTextEdit::focusInEvent(event);
}

void Coder::gotoLineEnd()
{
    QTextCursor cursor = textCursor();
    int length = cursor.block().text().length();
    if (length != 0)
    {
        int original  = cursor.position();
        QTextCursor::MoveMode mode = QTextCursor::MoveAnchor;
        if (QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
        { mode = QTextCursor::KeepAnchor; }
        cursor.movePosition(QTextCursor::StartOfLine, mode);
        int start = cursor.position();
        cursor.movePosition(QTextCursor::EndOfLine, mode);
        int i = length;
        while (cursor.block().text()[i - 1].isSpace())
        {
            i--;
            if (i == 1)
            {
                i = length;
                break;
            }
        }
        if ((original == start) || ((start + i) != original))
        { cursor.setPosition(start + i, mode); }
        setTextCursor(cursor);
    }
}

void Coder::gotoLineStart()
{
    QTextCursor c = textCursor();
    int length = c.block().text().length();
    if (length != 0)
    {
        int original  = c.position();
        QTextCursor::MoveMode mode = QTextCursor::MoveAnchor;
        if (QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
        { mode = QTextCursor::KeepAnchor; }
        c.movePosition(QTextCursor::StartOfLine, mode);
        int start = c.position();
        int i = 0;
        while (c.block().text()[i].isSpace())
        {
            i++;
            if (i == length)
            {
                i = 0;
                break;
            }
        }
        if ((original == start) || ((start + i) != original))
        { c.setPosition(start + i, mode); }
        setTextCursor(c);
    }
}

void Coder::onCursorPositionChanged()
{
    QList<QTextEdit::ExtraSelection> selections;
    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection s;
        static QColor h = palette().color(QPalette::Text);
        h.setAlpha(25);
        s.format.setBackground(h);
        s.format.setProperty(QTextCharFormat::FullWidthSelection, true);
        s.cursor = textCursor();
        s.cursor.clearSelection();
        selections.append(s);
    }
    setExtraSelections(selections);
}

void Coder::onInit()
{
    onCursorPositionChanged();
    onUpdateMargins(0);
}

void Coder::onUpdateRequest(const QRect &rect, const int column)
{
    if (column)
    { _sidebar->scroll(0, column); }
    _sidebar->update(0, rect.y(), _sidebar->width(), rect.height());
    if (rect.contains(viewport()->rect()))
    { onUpdateMargins(0); }
}

bool Coder::indentText(const bool forward)
{
    QTextCursor cursor = textCursor();
    QTextCursor clone = cursor;
    if (!cursor.hasSelection())
    { return false; }
    int start = cursor.selectionStart();
    cursor.setPosition(cursor.selectionStart());
    clone.setPosition(clone.selectionEnd());
    int stop = clone.blockNumber();
    cursor.beginEditBlock();
    do
    {
        int position = cursor.position();
        QString text = cursor.block().text();
        int count = indentSize(text);
        if (forward)
        { count++; }
        else if (count > 0)
        { count--; }
        cursor.select(QTextCursor::LineUnderCursor);
        if (forward)
        { cursor.insertText(_spacesForTabs ? QString(_tabStopWidth, ' ') + text : QChar('\t') + text); }
        else
        { cursor.insertText(addIndent(text, count)); }
        cursor.setPosition(position);
        if (!cursor.movePosition(QTextCursor::NextBlock))
        { break; }
    }
    while(cursor.blockNumber() <= stop);
    cursor.setPosition(start, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
    while (cursor.block().blockNumber() < stop)
    { cursor.movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor); }
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.endEditBlock();
    setTextCursor(cursor);
    return true;
}

int Coder::indentSize(const QString &text)
{
    int count = 0;
    int i = 0;
    int length = text.length();
    if (length == 0)
    { return 0; }
    QChar current = text.at(i);
    while ((i < length) && ((current == ' ') || (current == QChar('\t'))))
    {
        if (current == QChar('\t'))
        {
            count++;
            i++;
        }
        else if (current == ' ')
        {
            int j = 0;
            while ((i + j < length) && (text.at(i + j) == ' '))
            { j++; }
            i += j;
            count += j / _tabStopWidth;
        }
        if (i < length)
        { current = text.at(i); }
    }
    return count;
}

void Coder::keyPressEvent(QKeyEvent *event)
{
    QTextCursor cursor = textCursor();
    switch (event->key())
    {
    case Qt::Key_Backtab:
    case Qt::Key_Tab:
    {
        bool forward = !QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier);
        if (indentText(forward))
        { return; }
        else if (forward)
        {
            QString text = _spacesForTabs ? QString(_tabStopWidth, ' ') : QChar('\t');
            QTextCursor cursor = textCursor();
            cursor.insertText(text);
            setTextCursor(cursor);
            return;
        }
        break;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return:
        break;
    case Qt::Key_Down:
    case Qt::Key_Up:
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
        {
            if (event->key() == Qt::Key_Down)
            { verticalScrollBar()->triggerAction(QAbstractSlider::SliderSingleStepAdd); }
            else
            { verticalScrollBar()->triggerAction(QAbstractSlider::SliderSingleStepSub); }
            event->accept();
        }
        break;
    case Qt::Key_Escape:
        if (cursor.hasSelection())
        {
            cursor.clearSelection();
            setTextCursor(cursor);
            event->accept();
        }
        break;
    case Qt::Key_Home:
    case Qt::Key_End:
        if (!QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
        {
            if (event->key() == Qt::Key_Home)
            { gotoLineStart(); }
            else
            { gotoLineEnd(); }
            event->accept();
        }
        return;
    case Qt::Key_PageDown:
    case Qt::Key_PageUp:
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
        {
            if (event->key() == Qt::Key_Down)
            { verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepAdd); }
            else
            { verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepSub); }
            event->accept();
        }
        break;
    default:
        break;
    }
    QPlainTextEdit::keyPressEvent(event);
}

void Coder::paintEvent(QPaintEvent *event)
{
    QPainter line(viewport());
    const int offset = (fontMetrics().width('8') * 80)
            + contentOffset().x()
            + document()->documentMargin();
    QPen pen = line.pen();
    pen.setColor(palette().color(QPalette::AlternateBase));
    pen.setStyle(Qt::DotLine);
    line.setPen(pen);
    line.drawLine(offset, 0, offset, viewport()->height());
    QPlainTextEdit::paintEvent(event);
}

void Coder::moveLine(const bool up)
{
    QTextCursor original = textCursor();
    QTextCursor moved = original;
    moved.setVisualNavigation(false);
    moved.beginEditBlock();
    bool selected = original.hasSelection();
    if (selected)
    {
        moved.setPosition(original.selectionStart());
        moved.movePosition(QTextCursor::StartOfBlock);
        moved.setPosition(original.selectionEnd(), QTextCursor::KeepAnchor);
        moved.movePosition(moved.atBlockStart() ? QTextCursor::Left : QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    }
    else
    {
        moved.movePosition(QTextCursor::StartOfBlock);
        moved.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    }
    QString text = moved.selectedText();
    moved.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
    moved.removeSelectedText();
    if (up)
    {
        moved.movePosition(QTextCursor::PreviousBlock);
        moved.insertBlock();
        moved.movePosition(QTextCursor::Left);
    }
    else
    {
        moved.movePosition(QTextCursor::EndOfBlock);
        if (moved.atBlockStart())
        {
            moved.movePosition(QTextCursor::NextBlock);
            moved.insertBlock();
            moved.movePosition(QTextCursor::Left);
        }
        else
        { moved.insertBlock(); }
    }
    int start = moved.position();
    moved.clearSelection();
    moved.insertText(text);
    int end = moved.position();
    if (selected)
    {
        moved.setPosition(start);
        moved.setPosition(end, QTextCursor::KeepAnchor);
    }
    moved.endEditBlock();
    setTextCursor(moved);
}

void Coder::onMoveLineDown()
{
    moveLine(false);
}

void Coder::onMoveLineUp()
{
    moveLine(true);
}

void Coder::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    QRect rect = contentsRect();
    _sidebar->setGeometry(QRect(rect.left(), rect.top(), _sidebar->sizeHint().width(), rect.height()));
}

void Coder::setCurrentRow(const int r)
{
    QTextCursor c = textCursor();
    c.setPosition(r);
    setTextCursor(c);
}

void Coder::setFont(const QFont &f)
{
    QFont newer(f);
    newer.setFixedPitch(true);
    newer.setPointSize(10);
    newer.setStyleHint(QFont::Monospace);
    QPlainTextEdit::setFont(newer);
    setTabStopWidth(_tabStopWidth);
}

void Coder::setTabStopWidth(const int w)
{
    _tabStopWidth = w;
    QPlainTextEdit::setTabStopWidth(w * fontMetrics().width('8'));
}

void Coder::transformTo(const bool upper)
{
    QTextCursor c = currentTextCursor();
    QString before = c.selectedText();
    QString after = upper ? before.toUpper() : before.toLower();
    if (before != after)
    {
        c.beginEditBlock();
        c.deleteChar();
        c.insertText(after);
        c.endEditBlock();
        setTextCursor(c);
    }
}

void Coder::onTransformToLower()
{
    transformTo(false);
}

void Coder::onTransformToUpper()
{
    transformTo(true);
}

void Coder::onUpdateMargins(const int count)
{
    Q_UNUSED(count)
    setViewportMargins(_sidebar->sizeHint().width(), 0, 0, 0);
}

void Coder::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        const int delta = event->delta();
        if (delta > 0)
        { zoomIn();  }
        else if (delta < 0)
        { zoomOut(); }
    }
    else
    { QPlainTextEdit::wheelEvent(event); }
}

Coder::~Coder()
{
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
