#ifndef SPLASHWINDOW_H
#define SPLASHWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include "binaryversionsthread.h"

class SplashWindow : public QMainWindow
{
    Q_OBJECT

public:
    SplashWindow();
    ~SplashWindow();

private:
    QLabel *m_LabelVersions;
    QString mVersionApktool;
    QString mVersionJadx;
    QString mVersionJava;
    BinaryVersionsThread *m_VersionsThread;
    QWidget *buildCentralWidget();
    void rewriteVersionsText();

private slots:
    void handleVersionFailed(const QString &binary);
    void handleVersionResolved(const QString &binary, const QString &version);
    void handleVersionSuccess();
    void resolveVersions();
};

#endif // SPLASHWINDOW_H
