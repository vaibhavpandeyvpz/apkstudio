#ifndef TASKSPANELUI_H
#define TASKSPANELUI_H

#include <QWidget>

class TasksPanelUI : public QWidget
{
    Q_OBJECT
private:
    void prepare();
public:
    explicit TasksPanelUI(QWidget *parent) :
        QWidget(parent) {
        prepare();
    }
    ~TasksPanelUI() {
    }
};

#endif // TASKSPANELUI_H
