#ifndef PROJECTSPANELUI_H
#define PROJECTSPANELUI_H

#include <QWidget>

class ProjectsPanelUI : public QWidget
{
    Q_OBJECT
private:
    void prepare();
public:
    explicit ProjectsPanelUI(QWidget *parent = 0)
        : QWidget(parent) {
        prepare();
    }
    ~ProjectsPanelUI() {
    }
};

#endif // PROJECTSPANELUI_H
