#ifndef FILESPANELUI_H
#define FILESPANELUI_H

#include <QWidget>

class FilesPanelUI : public QWidget
{
    Q_OBJECT
private:
    void prepare();
public:
    explicit FilesPanelUI(QWidget *parent = 0)
        : QWidget(parent) {
        prepare();
    }
    ~ProjectsPanel() {
    }
};

#endif // FILESPANELUI_H
