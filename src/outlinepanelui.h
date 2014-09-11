#ifndef OUTLINEPANELUI_H
#define OUTLINEPANELUI_H

#include <QWidget>

class OutlinePanelUI : public QWidget
{
    Q_OBJECT
private:
    void prepare();
public:
    explicit OutlinePanelUI(QWidget *parent = 0) :
        QWidget(parent) {
        prepare();
    }
    ~OutlinePanelUI() {
    }
};

#endif // OUTLINEPANELUI_H
