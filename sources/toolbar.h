#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include "macros.h"

AS_NAMESPACE_START

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = 0);
};

AS_NAMESPACE_END

#endif // TOOLBAR_H
