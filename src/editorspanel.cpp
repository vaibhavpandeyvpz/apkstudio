#include "editorspanel.h"

void EditorsPanel::inflate()
{
    EditorWidget *ew = new EditorWidget(this);
    _splitter->addWidget(ew);
    ew->invalidate();
}
