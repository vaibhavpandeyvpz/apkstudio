#ifndef PROJECTSPANELUI_H
#define PROJECTSPANELUI_H

#include "panelui.h"
#include "utility.h"

class ProjectsPanelUI : public PanelUI
{
    Q_OBJECT
private:
    void inflate();
protected:
    static QString translate(const char *key) {
        return Utility::translate("projects", key);
    }
public:
    explicit ProjectsPanelUI(QWidget *parent = 0)
        : PanelUI(parent) {
        inflate();
    }
    ~ProjectsPanelUI() {
    }
};

#endif // PROJECTSPANELUI_H
