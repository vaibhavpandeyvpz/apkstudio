#ifndef LOGSPANELUI_H
#define LOGSPANELUI_H

#include "panelui.h"
#include "utility.h"

class LogsPanelUI : public PanelUI
{
    Q_OBJECT
private:
    void inflate();
protected:
    static QString translate(const char *key) {
        return Utility::translate("logs", key);
    }
public:
    explicit LogsPanelUI(QWidget *parent = 0) :
        PanelUI(parent) {
        inflate();
    }
    ~LogsPanelUI() {
    }
};

#endif // LOGSPANELUI_H
