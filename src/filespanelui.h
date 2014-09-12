#ifndef FILESPANELUI_H
#define FILESPANELUI_H

#include "panelui.h"
#include "utility.h"

class FilesPanelUI : public PanelUI
{
    Q_OBJECT
private:
    void inflate();
protected:
    static QString translate(const char *key) {
        return Utility::translate("files", key);
    }
public:
    explicit FilesPanelUI(QWidget *parent = 0)
        : PanelUI(parent) {
        inflate();
    }
    ~FilesPanelUI() {
    }
};

#endif // FILESPANELUI_H
