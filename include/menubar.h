#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include "macros.h"

APP_NAMESPACE_START

class MenuBar : public QMenuBar
{
    Q_OBJECT
private:
    APP_CONNECTIONS_LIST
private:
    void addEditMenu();
    void addFileMenu();
    void addHelpMenu();
    void addProjectMenu();
public:
    explicit MenuBar(QWidget *parent = 0);
    ~MenuBar();
};

APP_NAMESPACE_END

#endif // ASMENUBAR_H
