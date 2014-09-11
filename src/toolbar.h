#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QTextCodec>

#include "settings.h"
#include "toolbarui.h"

class ToolBar : public ToolBarUI
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = 0)
        : ToolBarUI(parent) {
    }
    ~ToolBar() {
    }
public:
    void invalidate();
};

#endif // TOOLBAR_H
