#include "linenumbers.hpp"
#include "coder.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

LineNumbers::LineNumbers(Coder *coder)
    : QWidget(coder) {
    this->coder = coder;
}

QSize LineNumbers::sizeHint() const
{
    int digits = 1;
    int max = qMax(1, coder->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    digits++;
    digits++;
    return QSize((3 + coder->fontMetrics().width('8') * digits), 0);
}

void LineNumbers::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(event->rect(), colors.first);
    QTextBlock block = coder->getFirstVisibleBlock();
    int number = block.blockNumber();
    int top = (int) coder->getBlockBoundingGeometry(block).translated(coder->getContentOffset()).top();
    int bottom = top + (int) coder->getBlockBoundingRect(block).height();
    while (block.isValid() && (top <= event->rect().bottom())) {
        if (block.isVisible() && (bottom >= event->rect().top())) {
            QString text = QString::number(number + 1).append(' ');
            painter.setPen(colors.second);
            painter.drawLine(event->rect().topRight(), event->rect().bottomRight());
            painter.drawText(0, top, width(), coder->fontMetrics().height(), Qt::AlignRight, text);
        }
        block = block.next();
        top = bottom;
        bottom = (top + ((int) coder->getBlockBoundingRect(block).height()));
        ++number;
    }
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
