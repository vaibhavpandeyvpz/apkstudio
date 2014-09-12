#ifndef EDITORSPANELUI_H
#define EDITORSPANELUI_H

#include "editorwidget.h"
#include "panelui.h"
#include "utility.h"

class EditorsPanelUI : public PanelUI
{
    Q_OBJECT
private:
    void prepare();
protected:
    static QString translate(const char *key) {
        return Utility::translate("editors", key);
    }
public:
    explicit EditorsPanelUI(QWidget *parent = 0)
        : PanelUI(parent) {
        prepare();
    }
    ~EditorsPanelUI() {
    }
};

#endif // EDITORSPANELUI_H
