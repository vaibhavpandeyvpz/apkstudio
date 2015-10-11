#include <QPainter>
#include "include/coder.h"
#include "include/codersidebar.h"
#include "include/constants.h"

APP_NAMESPACE_START

CoderSidebar::CoderSidebar(Coder *c) :
    QWidget(c), _coder(c)
{
}

void CoderSidebar::leaveEvent(QEvent *e)
{
    Q_UNUSED(e)
    QMouseEvent f(QEvent::MouseMove, QPoint(-1, -1), Qt::NoButton, 0, 0);
    mouseEvent(&f);
}

void CoderSidebar::mouseEvent(QMouseEvent *e)
{
    QTextCursor cursor = _coder->cursorForPosition(QPoint(0, e->pos().y()));
    if ((e->type() == QEvent::MouseButtonPress) && (e->button() == Qt::LeftButton))
    {
        QTextCursor s = cursor;
        s.setVisualNavigation(true);
        s.movePosition(QTextCursor::EndOfBlock);
        s.movePosition(QTextCursor::StartOfBlock, QTextCursor::KeepAnchor);
        _coder->setTextCursor(s);
    }
}

void CoderSidebar::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QTextBlock b = _coder->getFirstVisibleBlock();
    int n = b.blockNumber();
    int top = (int) _coder->getBlockBoundingGeometry(b).translated(_coder->getContentOffset()).top();
    int bottom = top + (int) _coder->getBlockBoundingRect(b).height();
    QRect full = e->rect();
    p.fillRect(full, palette().color(QPalette::Base));
    while (b.isValid() && (top <= full.bottom()))
    {
        if (b.isVisible() && (bottom >= full.top()))
        {
            QRect box(0, top, width(), _coder->fontMetrics().height());
            QFont f = p.font();
            f.setFamily(_coder->font().family());
            f.setPointSize(_coder->font().pointSize());
            if (_coder->textCursor().blockNumber() == n)
            {
                p.fillRect(box, palette().color(QPalette::Highlight));
                p.setPen(palette().color(QPalette::HighlightedText));
                f.setWeight(QFont::Bold);
            }
            else
            {
                f.setWeight(QFont::Normal);
                p.setPen(palette().color(QPalette::Text));
            }
            p.setFont(f);
            p.drawText(box.left(), box.top(), box.width(), box.height(), Qt::AlignRight, QString::number(n + 1).append(' '));
            p.setPen(palette().color(QPalette::Highlight));
            p.drawLine(full.topRight(), full.bottomRight());
        }
        b = b.next();
        top = bottom;
        bottom = (top + ((int) _coder->getBlockBoundingRect(b).height()));
        ++n;
    }
}

QSize CoderSidebar::sizeHint() const
{
    int d = 1;
    int m = qMax(1, _coder->blockCount());
    while (m >= 10)
    {
        m /= 10;
        ++d;
    }
    d++;
    d++;
    return QSize((3 + (_coder->fontMetrics().width('8') * d)), 0);
}

void CoderSidebar::wheelEvent(QWheelEvent *e)
{
    QCoreApplication::sendEvent(_coder->viewport(), e);
}

APP_NAMESPACE_END
