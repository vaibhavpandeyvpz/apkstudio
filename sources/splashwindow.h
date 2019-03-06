#ifndef SPLASHWINDOW_H
#define SPLASHWINDOW_H

#include <QLabel>
#include <QMainWindow>

class SplashWindow : public QMainWindow
{
    Q_OBJECT
public:
    SplashWindow();
    ~SplashWindow();
private:
    QWidget *buildCentralWidget();
};

#endif // SPLASHWINDOW_H
