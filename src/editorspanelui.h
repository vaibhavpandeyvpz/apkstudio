#ifndef EDITORSPANELUI_H
#define EDITORSPANELUI_H

#include <QWidget>

class EditorsPanelUI : public QWidget
{
    Q_OBJECT
private:
    void prepare();
public:
    explicit EditorsPanelUI(QWidget *parent = 0)
        : QWidget(parent) {
        prepare();
    }
    ~EditorsPanelUI() {
    }
};

#endif // EDITORSPANELUI_H
