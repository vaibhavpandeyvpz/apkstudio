#include <QApplication>
#include <QFileInfo>
#include <QPainter>
#include <QScrollBar>
#include <QSettings>
#include <QShortcut>
#include <QTextBlock>
#include <QTextStream>
#include "sourcecodeedit.h"
#include "themedsyntaxhighlighter.h"

#define TAB_STOP_WIDTH 4
#define TABS_TO_SPACES true

SourceCodeEdit::SourceCodeEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
    m_Sidebar = new SourceCodeSidebarWidget(this);
    QSettings settings;
    QFont font;
#ifdef Q_OS_WIN
    font.setFamily(settings.value("editor_font", "Courier New").toString());
#elif defined(Q_OS_MACOS)
    font.setFamily(settings.value("editor_font", "Monaco").toString());
#else
    font.setFamily(settings.value("editor_font", "Ubuntu Mono").toString());
#endif
    font.setFixedPitch(true);
    font.setPointSize(settings.value("editor_font_size", 10).toInt());
    font.setStyleHint(QFont::Monospace);
    const bool whitespaces = settings.value("editor_whitespaces", false).toBool();
    if (whitespaces) {
        QTextOption options;
        options.setFlags(QTextOption::ShowTabsAndSpaces);
        document()->setDefaultTextOption(options);
    }
    setCursorWidth(2);
    setFrameStyle(QFrame::NoFrame);
    setFont(font);
    setTabChangesFocus(false);
    setWordWrapMode(QTextOption::NoWrap);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &SourceCodeEdit::handleCursorPositionChanged);
    connect(this, &QPlainTextEdit::blockCountChanged, this, &SourceCodeEdit::handleBlockCountChanged);
    connect(this, &QPlainTextEdit::textChanged, this, &SourceCodeEdit::handleTextChanged);
    connect(this, &QPlainTextEdit::updateRequest, this, &SourceCodeEdit::handleUpdateRequest);
    connect(new QShortcut(Qt::CTRL | Qt::Key_U, this), &QShortcut::activated, [=] {
        transformText(true);
    });
    connect(new QShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_U, this), &QShortcut::activated, [=] {
        transformText(false);
    });
    connect(new QShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_Up, this), &QShortcut::activated, [=] {
        moveSelection(true);
    });
    connect(new QShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_Down, this), &QShortcut::activated, [=] {
        moveSelection(false);
    });
}

QRectF SourceCodeEdit::blockBoundingGeometryProxy(const QTextBlock &block)
{
    return blockBoundingGeometry(block);
}

QRectF SourceCodeEdit::blockBoundingRectProxy(const QTextBlock &block)
{
    return blockBoundingRect(block);
}

QPointF SourceCodeEdit::contentOffsetProxy()
{
    return contentOffset();
}

QString SourceCodeEdit::filePath()
{
    return m_FilePath;
}

QTextBlock SourceCodeEdit::firstVisibleBlockProxy()
{
    return firstVisibleBlock();
}

void SourceCodeEdit::gotoLine(const int no)
{
    QTextCursor cursor(document()->findBlockByLineNumber(no - 1));
    setTextCursor(cursor);
}

void SourceCodeEdit::handleBlockCountChanged(const int count)
{
    Q_UNUSED(count)
    setViewportMargins(m_Sidebar->sizeHint().width(), 0, 0, 0);
}

void SourceCodeEdit::handleCursorPositionChanged()
{
    QList<QTextEdit::ExtraSelection> selections;
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        static QColor highlight = palette().color(QPalette::Text);
        highlight.setAlpha(25);
        selection.format.setBackground(highlight);
        selection.format.setProperty(QTextCharFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        selections.append(selection);
    }
    setExtraSelections(selections);
}

void SourceCodeEdit::handleUpdateRequest(const QRect &rect, const int column)
{
    if (column) {
        m_Sidebar->scroll(0, column);
    }
    m_Sidebar->update(0, rect.y(), m_Sidebar->width(), rect.height());
    if (rect.contains(viewport()->rect())) {
        handleBlockCountChanged(0);
    }
}

void SourceCodeEdit::handleTextChanged()
{
    handleCursorPositionChanged();
    handleBlockCountChanged(0);
}

int SourceCodeEdit::indentSize(const QString &text)
{
    int count = 0;
    int i = 0;
    int length = text.length();
    if (length == 0) {
        return 0;
    }
    QChar current = text.at(i);
    while ((i < length) && ((current == ' ') || (current == QChar('\t')))) {
        if (current == QChar('\t')) {
            count++;
            i++;
        } else if (current == ' ') {
            int j = 0;
            while ((i + j < length) && (text.at(i + j) == ' ')) {
                j++;
            }
            i += j;
            count += j / TAB_STOP_WIDTH;
        }
        if (i < length) {
            current = text.at(i);
        }
    }
    return count;
}

bool SourceCodeEdit::indentText(const bool forward)
{
    QTextCursor cursor = textCursor();
    QTextCursor clone = cursor;
    if (!cursor.hasSelection()) {
        return false;
    }
    int start = cursor.selectionStart();
    cursor.setPosition(cursor.selectionStart());
    clone.setPosition(clone.selectionEnd());
    int stop = clone.blockNumber();
    cursor.beginEditBlock();
    do {
        int position = cursor.position();
        QString text = cursor.block().text();
        int count = indentSize(text);
        if (forward) {
            count++;
        } else if (count > 0) {
            count--;
        }
        cursor.select(QTextCursor::LineUnderCursor);
        if (forward) {
            cursor.insertText(TABS_TO_SPACES ? QString(TAB_STOP_WIDTH, ' ') + text : QChar('\t') + text);
        } else {
            cursor.insertText(indentText(text, count));
        }
        cursor.setPosition(position);
        if (!cursor.movePosition(QTextCursor::NextBlock)) {
            break;
        }
    }
    while(cursor.blockNumber() <= stop);
    cursor.setPosition(start, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
    while (cursor.block().blockNumber() < stop) {
        cursor.movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor);
    }
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.endEditBlock();
    setTextCursor(cursor);
    return true;
}

QString SourceCodeEdit::indentText(QString text, int count) const
{
    if (text.isEmpty()) {
        return text;
    }
    while ((text.at(0) == ' ') || (text.at(0) == '\t')) {
        text.remove(0, 1);
        if (text.isEmpty()) {
            break;
        }
    }
    while (count != 0) {
        text = text.insert(0, TABS_TO_SPACES ? QString(TAB_STOP_WIDTH, ' ') : QChar('\t'));
        count--;
    }
    return text;
}

void SourceCodeEdit::keyPressEvent(QKeyEvent *event)
{
    QTextCursor cursor = textCursor();
    switch (event->key()) {
    case Qt::Key_Backtab:
    case Qt::Key_Tab: {
        bool forward = !QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier);
        if (indentText(forward)) {
            event->accept();
            return;
        } else if (forward) {
            QString text = TABS_TO_SPACES ? QString(TAB_STOP_WIDTH, ' ') : QChar('\t');
            QTextCursor cursor = textCursor();
            cursor.insertText(text);
            setTextCursor(cursor);
            event->accept();
            return;
        }
        break;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return:
        break;
    case Qt::Key_Down:
    case Qt::Key_Up:
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))  {
            if (event->key() == Qt::Key_Down) {
                verticalScrollBar()->triggerAction(QAbstractSlider::SliderSingleStepAdd);
            } else {
                verticalScrollBar()->triggerAction(QAbstractSlider::SliderSingleStepSub);
            }
            event->accept();
        }
        break;
    case Qt::Key_Escape:
        if (cursor.hasSelection()) {
            cursor.clearSelection();
            setTextCursor(cursor);
            event->accept();
        }
        break;
    case Qt::Key_Home:
    case Qt::Key_End:
        if (!QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
            moveCursor(event->key() != Qt::Key_Home);
            event->accept();
        }
        return;
    case Qt::Key_PageDown:
    case Qt::Key_PageUp:
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
            if (event->key() == Qt::Key_Down) {
                verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepAdd);
            } else {
                verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepSub);
            }
            event->accept();
        }
        break;
    default:
        break;
    }
    QPlainTextEdit::keyPressEvent(event);
}

void SourceCodeEdit::moveCursor(const bool end)
{
    QTextCursor cursor = textCursor();
    int length = cursor.block().text().length();
    if (length != 0) {
        int original  = cursor.position();
        QTextCursor::MoveMode mode = QTextCursor::MoveAnchor;
        if (QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
            mode = QTextCursor::KeepAnchor;
        }
        cursor.movePosition(QTextCursor::StartOfLine, mode);
        int start = cursor.position();
        int i;
        if (end) {
            cursor.movePosition(QTextCursor::EndOfLine, mode);
            i = length;
            while (cursor.block().text()[i - 1].isSpace()) {
                i--;
                if (i == 1) {
                    i = length;
                    break;
                }
            }
        } else {
            i = 0;
            while (cursor.block().text()[i].isSpace()) {
                i++;
                if (i == length) {
                    i = 0;
                    break;
                }
            }
        }
        if ((original == start) || ((start + i) != original)) {
            cursor.setPosition(start + i, mode);
        }
        setTextCursor(cursor);
    }
}

void SourceCodeEdit::moveSelection(const bool up)
{
    QTextCursor original = textCursor();
    QTextCursor moved = original;
    moved.setVisualNavigation(false);
    moved.beginEditBlock();
    bool selected = original.hasSelection();
    if (selected) {
        moved.setPosition(original.selectionStart());
        moved.movePosition(QTextCursor::StartOfBlock);
        moved.setPosition(original.selectionEnd(), QTextCursor::KeepAnchor);
        moved.movePosition(moved.atBlockStart() ? QTextCursor::Left : QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    } else {
        moved.movePosition(QTextCursor::StartOfBlock);
        moved.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    }
    QString text = moved.selectedText();
    moved.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
    moved.removeSelectedText();
    if (up) {
        moved.movePosition(QTextCursor::PreviousBlock);
        moved.insertBlock();
        moved.movePosition(QTextCursor::Left);
    } else {
        moved.movePosition(QTextCursor::EndOfBlock);
        if (moved.atBlockStart()) {
            moved.movePosition(QTextCursor::NextBlock);
            moved.insertBlock();
            moved.movePosition(QTextCursor::Left);
        } else {
            moved.insertBlock();
        }
    }
    int start = moved.position();
    moved.clearSelection();
    moved.insertText(text);
    int end = moved.position();
    if (selected) {
        moved.setPosition(start);
        moved.setPosition(end, QTextCursor::KeepAnchor);
    }
    moved.endEditBlock();
    setTextCursor(moved);
}

void SourceCodeEdit::open(const QString &path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        auto content = QString::fromUtf8(file.readAll());
        setPlainText(content);
        QFileInfo info(path);
        QString extension = info.suffix().toLower();
        QSettings settings;
        const bool dark = settings.value("dark_theme", false).toBool();
        new ThemedSyntaxHighlighter(
                    ThemedSyntaxHighlighter::theme(dark ? "dark" : "light"),
                    ThemedSyntaxHighlighter::definitions(extension),
                    document());
    }
    m_FilePath = path;
}

void SourceCodeEdit::paintEvent(QPaintEvent *event)
{
    QPainter line(viewport());
    const int offset = static_cast<int>((fontMetrics().width('8') * 80)
                                        + contentOffset().x()
                                        + document()->documentMargin());
    QPen pen = line.pen();
    static QColor eol = palette().color(QPalette::Text);
    eol.setAlpha(50);
    pen.setColor(eol);
    pen.setStyle(Qt::DotLine);
    line.setPen(pen);
    line.drawLine(offset, 0, offset, viewport()->height());
    QPlainTextEdit::paintEvent(event);
}

void SourceCodeEdit::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    QRect rect = contentsRect();
    m_Sidebar->setGeometry(QRect(rect.left(), rect.top(), m_Sidebar->sizeHint().width(), rect.height()));
}

bool SourceCodeEdit::save()
{
    QFile file(m_FilePath);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out.setGenerateByteOrderMark(false);
        out << toPlainText();
        out.flush();
        file.close();
        return true;
    }
    return false;
}

void SourceCodeEdit::transformText(const bool upper)
{
    QTextCursor cursor = textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    QString before = cursor.selectedText();
    QString after = upper ? before.toUpper() : before.toLower();
    if (before != after) {
        cursor.beginEditBlock();
        cursor.deleteChar();
        cursor.insertText(after);
        cursor.endEditBlock();
        setTextCursor(cursor);
    }
}

void SourceCodeEdit::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        const int delta = event->delta();
        if (delta > 0) {
            zoomIn();
        } else if (delta < 0) {
            zoomOut();
        }
    } else {
        QPlainTextEdit::wheelEvent(event);
    }
}

SourceCodeSidebarWidget::SourceCodeSidebarWidget(SourceCodeEdit *edit)
    : QWidget(edit), m_Edit(edit)
{
}

void SourceCodeSidebarWidget::leaveEvent(QEvent *e)
{
    Q_UNUSED(e)
    QMouseEvent copy(QEvent::MouseMove, QPoint(-1, -1), Qt::NoButton, nullptr, nullptr);
    mouseEvent(&copy);
}

void SourceCodeSidebarWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QTextBlock block = m_Edit->firstVisibleBlockProxy();
    int i = block.blockNumber();
    int top = static_cast<int>(m_Edit->blockBoundingGeometryProxy(block).translated(m_Edit->contentOffsetProxy()).top());
    int bottom = top + static_cast<int>(m_Edit->blockBoundingRectProxy(block).height());
    QRect full = e->rect();
    painter.fillRect(full, palette().color(QPalette::Base));
    while (block.isValid() && (top <= full.bottom())) {
        if (block.isVisible() && (bottom >= full.top())) {
            QRect box(0, top, width(), m_Edit->fontMetrics().height());
            QFont font = painter.font();
            font.setFamily(m_Edit->font().family());
            font.setPointSize(m_Edit->font().pointSize());
            if (m_Edit->textCursor().blockNumber() == i) {
                painter.fillRect(box, palette().color(QPalette::Highlight));
                painter.setPen(palette().color(QPalette::HighlightedText));
                font.setWeight(QFont::Bold);
            } else {
                font.setWeight(QFont::Normal);
                painter.setPen(palette().color(QPalette::Text));
            }
            painter.setFont(font);
            painter.drawText(box.left(), box.top(), box.width(), box.height(), Qt::AlignRight, QString::number(i + 1).append(' '));
            painter.setPen(palette().color(QPalette::Highlight));
            painter.drawLine(full.topRight(), full.bottomRight());
        }
        block = block.next();
        top = bottom;
        bottom = (top + static_cast<int>(m_Edit->blockBoundingRectProxy(block).height()));
        ++i;
    }
}

void SourceCodeSidebarWidget::mouseEvent(QMouseEvent *e)
{
    QTextCursor cursor = m_Edit->cursorForPosition(QPoint(0, e->pos().y()));
    if ((e->type() == QEvent::MouseButtonPress) && (e->button() == Qt::LeftButton)) {
        cursor.movePosition(QTextCursor::EndOfBlock);
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::KeepAnchor);
        cursor.setVisualNavigation(true);
        m_Edit->setTextCursor(cursor);
    }
}

void SourceCodeSidebarWidget::mouseMoveEvent(QMouseEvent *event)
{
    mouseEvent(event);
}
void SourceCodeSidebarWidget::mousePressEvent(QMouseEvent *event)
{
    mouseEvent(event);
}
void SourceCodeSidebarWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mouseEvent(event);
}

QSize SourceCodeSidebarWidget::sizeHint() const
{
    int digits = 1;
    int blocks = qMax(1, m_Edit->blockCount());
    while (blocks >= 10) {
        blocks /= 10;
        digits++;
    }
    digits++;
    digits++;
    return QSize((3 + (m_Edit->fontMetrics().width('8') * digits)), 0);
}

void SourceCodeSidebarWidget::wheelEvent(QWheelEvent *e)
{
    QApplication::sendEvent(m_Edit->viewport(), e);
}
