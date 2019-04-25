#ifndef SPLASHWINDOW_H
#define SPLASHWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMap>

class SplashWindow : public QMainWindow
{
    Q_OBJECT
public:
    SplashWindow();
    ~SplashWindow();
private:
    QMap<QString, QString> m_Versions;
    QWidget *buildCentralWidget();
private slots:
    void handleVersionResolved(const QString &binary, const QString &version);
    void handleVersionResolveFinished();
};

#endif // SPLASHWINDOW_H
