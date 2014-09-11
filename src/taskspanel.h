#ifndef TASKSPANEL_H
#define TASKSPANEL_H

#include "taskspanelui.h"

class TasksPanel : public TasksPanelUI
{
    Q_OBJECT
public:
    explicit TasksPanel(QWidget *parent = 0)
        : TasksPanelUI(parent) {
    }
    ~TasksPanel() {
    }
};

#endif // TASKSPANEL_H
