#ifndef TASKSPANELUI_H
#define TASKSPANELUI_H

#include "panelui.h"
#include "utility.h"

class TasksPanelUI : public PanelUI
{
    Q_OBJECT
private:
    void inflate();
protected:
    static QString translate(const char *key) {
        return Utility::translate("tasks", key);
    }
public:
    explicit TasksPanelUI(QWidget *parent) :
        PanelUI(parent) {
        inflate();
    }
    ~TasksPanelUI() {
    }
};

#endif // TASKSPANELUI_H
