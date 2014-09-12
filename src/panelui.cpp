#include "panelui.h"

void PanelUI::prepare()
{
    // Initialize: Self
    setMinimumSize(QSize(160, 160));
    // Initialize: Splitter
    _splitter = new QSplitter(this);
    // Add: Self
    QWidget* title = titleBarWidget();
    setTitleBarWidget(new QWidget(this));
    delete title;
    setWidget(_splitter);
}
