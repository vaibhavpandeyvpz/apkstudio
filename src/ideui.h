#ifndef IDEUI_H
#define IDEUI_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>

#include "menubar.h"
#include "settings.h"
#include "toolbar.h"
#include "utility.h"

class IDEUI : public QMainWindow
{
    Q_OBJECT
protected:
    int _exit_code;
    MenuBar *_menubar;
    ToolBar *_toolbar;
protected:
    static QString translate(const char *key) {
        return Utility::translate("ide", key);
    }
private:
    void closeEvent(QCloseEvent *event);
    void prepare();
public:
    explicit IDEUI(QWidget *parent = 0)
        : QMainWindow(parent) {
        prepare();
    }
    ~IDEUI() {
    }
public Q_SLOTS:
    void inflate();
};

#endif // IDEUI_H
