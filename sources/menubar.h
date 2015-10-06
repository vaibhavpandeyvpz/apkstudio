#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include "macros.h"

AS_NAMESPACE_START

class MenuBar : public QMenuBar
{
    Q_OBJECT
private:
    AS_CONNECTIONS_LIST
private:
    void addEditMenu();
    void addFileMenu();
    void addHelpMenu();
    void addProjectMenu();
public:
    explicit MenuBar(QWidget *parent = 0);
    ~MenuBar();
signals:
    void projectOpen(QString);
};

AS_NAMESPACE_END

#endif // ASMENUBAR_H
