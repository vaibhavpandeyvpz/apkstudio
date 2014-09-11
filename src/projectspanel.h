#ifndef PROJECTSPANEL_H
#define PROJECTSPANEL_H

#include "projectspanelui.h"

class ProjectsPanel : public ProjectsPanelUI
{
    Q_OBJECT
public:
    explicit ProjectsPanel(QWidget *parent = 0)
        : ProjectsPanelUI(parent) {
    }
    ~ProjectsPanel() {
    }
};

#endif // PROJECTSPANEL_H
