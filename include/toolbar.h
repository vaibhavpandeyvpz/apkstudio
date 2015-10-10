#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include "macros.h"

APP_NAMESPACE_START

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = 0);
};

APP_NAMESPACE_END

#endif // TOOLBAR_H
