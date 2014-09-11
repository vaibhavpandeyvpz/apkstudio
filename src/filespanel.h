#ifndef FILESPANEL_H
#define FILESPANEL_H

#include "filespanelui.h"

class FilesPanel : public FilesPanelUI
{
    Q_OBJECT
public:
    explicit FilesPanel(QWidget *parent = 0)
        : FilesPanelUI(parent) {
    }
    ~FilesPanel() {
    }
};

#endif // FILESPANEL_H
