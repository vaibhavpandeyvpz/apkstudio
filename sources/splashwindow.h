#ifndef SPLASHWINDOW_H
#define SPLASHWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMap>

class SplashWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SplashWindow(const QString &apkFilePath = QString());
    ~SplashWindow();
private:
    QMap<QString, QString> m_Versions;
    QString m_ApkFilePath;
    QWidget *buildCentralWidget();
private slots:
    void handleVersionResolved(const QString &binary, const QString &version);
    void handleVersionResolveFinished();
};

#endif // SPLASHWINDOW_H
