#ifndef OUTLINEPANEL_H
#define OUTLINEPANEL_H

#include "outlinepanelui.h"

class OutlinePanel : public OutlinePanelUI
{
    Q_OBJECT
public:
    explicit OutlinePanel(QWidget *parent = 0)
        : OutlinePanelUI(parent) {
    }
    ~OutlinePanel() {
    }
};

#endif // OUTLINEPANEL_H
