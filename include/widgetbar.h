#ifndef WIDGETBAR_H
#define WIDGETBAR_H

#include <QDockWidget>
#include <QToolBar>
#include "include/macros.h"

APP_NAMESPACE_START

class WidgetBar : public QToolBar
{
    Q_OBJECT
private:
    APP_CONNECTIONS_LIST
public:
    explicit WidgetBar(QWidget *parent = 0);
    ~WidgetBar();
public:
    void addWidget(const QIcon &icon, QDockWidget *widget);
};

APP_NAMESPACE_END

#endif // WIDGETBAR_H
