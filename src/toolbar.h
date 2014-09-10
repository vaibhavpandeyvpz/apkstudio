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
    void invalidate();
    ~ToolBar() {
    }
};

#endif // TOOLBAR_H
