#ifndef LOGSPANELUI_H
#define LOGSPANELUI_H

#include <QWidget>

class LogsPanelUI : public QWidget
{
    Q_OBJECT
private:
    void prepare();
public:
    explicit LogsPanelUI(QWidget *parent = 0) :
        QWidget(parent) {
        prepare();
    }
    ~LogsPanelUI() {
    }
};

#endif // LOGSPANELUI_H
