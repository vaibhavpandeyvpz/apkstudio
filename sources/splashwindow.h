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
    QLabel *m_LabelVersion;
    QLabel *m_LabelVersions;
    QString mVersionApktool;
    QString mVersionJadx;
    QString mVersionJava;
    QWidget *buildCentralWidget();
    void rewriteVersionsText();

private slots:
    void handleTimerTimeout();
};

#endif // SPLASHWINDOW_H
