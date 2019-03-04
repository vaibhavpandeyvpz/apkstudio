#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(512, 320);
    setWindowTitle(tr("APK Studio", "main").append(" - https://git.io/fhxGT"));
}

MainWindow::~MainWindow()
{
}
