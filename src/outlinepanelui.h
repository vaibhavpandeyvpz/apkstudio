#ifndef OUTLINEPANELUI_H
#define OUTLINEPANELUI_H

#include "panelui.h"
#include "utility.h"

class OutlinePanelUI : public PanelUI
{
    Q_OBJECT
private:
    void inflate();
protected:
    static QString translate(const char *key) {
        return Utility::translate("outline", key);
    }
public:
    explicit OutlinePanelUI(QWidget *parent = 0) :
        PanelUI(parent) {
        inflate();
    }
    ~OutlinePanelUI() {
    }
};

#endif // OUTLINEPANELUI_H
