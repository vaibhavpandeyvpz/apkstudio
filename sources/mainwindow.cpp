#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include "mainwindow.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle(tr("APK Studio", "main").append(" - https://git.io/fhxGT"));
    QSettings settings;
    if (settings.value("app_maximized").toBool()) {
        showMaximized();
    } else {
        resize(settings.value("app_size", QSize(WINDOW_WIDTH, WINDOW_HEIGHT)).toSize());
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    QSettings settings;
    bool maximized = isMaximized();
    settings.setValue("app_maximized", maximized);
    if (!maximized) {
        settings.setValue("app_size", size());
    }
    settings.sync();
}

MainWindow::~MainWindow()
{
}
