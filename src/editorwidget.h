#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include "editorwidgetui.h"
#include "imageeditor.h"

class EditorWidget : public EditorWidgetUI
{
    Q_OBJECT
public:
    explicit EditorWidget(QWidget *parent = 0)
        : EditorWidgetUI(parent) {
    }
    ~EditorWidget() {
    }
public:
    void invalidate();
};

#endif // EDITORWIDGET_H
