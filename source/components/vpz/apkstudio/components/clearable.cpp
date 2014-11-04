#include "clearable.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Clearable::Clearable(QWidget *parent) :
    QLineEdit(parent)
{
    empty = new QToolButton(this);
    empty->hide();
    empty->setCursor(QCursor(Qt::PointingHandCursor));
    empty->setIcon(::icon("cross_white"));
    empty->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    connections.append(connect(empty, &QToolButton::clicked, this, &Clearable::clear));
    connections.append(connect(this, &Clearable::textChanged, this, &Clearable::onTextChanged));
    setStyleSheet(QString(STYLESHEET_PREFIXED).arg(empty->sizeHint().width() + style()->pixelMetric(QStyle::PM_DefaultFrameWidth) + 1));
}

void Clearable::onTextChanged(const QString &text)
{
    empty->setVisible(!text.isEmpty());
}

void Clearable::resizeEvent(QResizeEvent *)
{
    QSize size = empty->sizeHint();
    empty->move((rect().right() - style()->pixelMetric(QStyle::PM_DefaultFrameWidth) - size.width()), (rect().bottom() + 1 - size.height()) / 2);
}

Clearable::~Clearable()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
