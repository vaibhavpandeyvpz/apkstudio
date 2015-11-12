#include "include/widgetbar.h"
#include <QAction>

APP_NAMESPACE_START

WidgetBar::WidgetBar(QWidget *parent)
    : QToolBar(parent)
{
}

void WidgetBar::addWidget(const QIcon &icon, QDockWidget *widget)
{
    QAction *action = new QAction(icon, widget->windowTitle(), this);
    action->setCheckable(true);
    action->setChecked(true);
    _connections << connect(widget, &QDockWidget::visibilityChanged, action, &QAction::setChecked);
    _connections << connect(action, &QAction::toggled, widget, &QDockWidget::setVisible);
    addAction(action);
}

WidgetBar::~WidgetBar()
{
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
