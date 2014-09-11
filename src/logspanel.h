#ifndef LOGSPANEL_H
#define LOGSPANEL_H

#include "logspanelui.h"

class LogsPanel : public LogsPanelUI
{
    Q_OBJECT
public:
    explicit LogsPanel(QWidget *parent = 0)
        : LogsPanelUI(parent) {
    }
    ~LogsPanel() {
    }
};

#endif // LOGSPANEL_H
