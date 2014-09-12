#include "editorwidget.h"

void EditorWidget::invalidate()
{
    // Add: Editor
    ImageEditor *ie = new ImageEditor(this);
    _hlayout->addWidget(ie);
    ie->open(QString("D:/test.png"));
}
