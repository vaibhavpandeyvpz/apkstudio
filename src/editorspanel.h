#ifndef EDITORSPANEL_H
#define EDITORSPANEL_H

#include "editorspanelui.h"
#include "imageeditor.h"

class EditorsPanel : public EditorsPanelUI
{
    Q_OBJECT
private:
    void inflate();
public:
    explicit EditorsPanel(QWidget *parent = 0)
        : EditorsPanelUI(parent) {
        inflate();
    }
    ~EditorsPanel() {
    }
};

#endif // EDITORSPANEL_H
