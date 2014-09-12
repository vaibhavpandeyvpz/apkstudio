#ifndef PANELUI_H
#define PANELUI_H

#include <QDockWidget>
#include <QSplitter>

#include "utility.h"

class PanelUI : public QDockWidget
{
    Q_OBJECT
private:
    void prepare();
protected:
    QSplitter *_splitter;
protected:
    static QIcon icon(const char *name) {
        return Utility::icon(name);
    }
public:
    explicit PanelUI(QWidget *parent = 0, Qt::WindowFlags flags = 0)
        : QDockWidget(parent, flags) {
        prepare();
    }
    ~PanelUI() {
    }
};

#endif // PANELUI_H
