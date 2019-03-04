#include <QPixmap>
#include <QVBoxLayout>
#include <QTimer>
#include "mainwindow.h"
#include "splashwindow.h"

#define SPLASH_WIDTH 512
#define SPLASH_HEIGHT 320

SplashWindow::SplashWindow()
    : QMainWindow(nullptr, Qt::SplashScreen)
{
    setCentralWidget(buildCentralWidget());
    setMaximumSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    setMinimumSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    QTimer::singleShot(1000, this, &SplashWindow::handleTimerTimeout);
}

QWidget *SplashWindow::buildCentralWidget()
{
    auto widget = new QWidget(this);
    auto layout = new QVBoxLayout(widget);
    QPixmap pixmap(":/images/splash.png");
    auto banner = new QLabel(this);
    banner->setPixmap(pixmap);
    layout->addWidget(banner);
    auto loading = new QLabel(widget);
    loading->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    loading->setContentsMargins(10, 0, 0, 72);
    loading->setFixedSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    loading->setStyleSheet("QLabel { color: white; }");
    loading->setText(tr("Loading..."));
    m_LabelVersion = new QLabel(widget);
    m_LabelVersion->setAlignment(Qt::AlignRight);
    m_LabelVersion->setContentsMargins(0, 2, 4, 0);
    m_LabelVersion->setFixedSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    m_LabelVersion->setStyleSheet("QLabel { color: white; }");
    m_LabelVersion->setText("1.0.0");
    m_LabelVersions = new QLabel(widget);
    m_LabelVersions->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    m_LabelVersions->setContentsMargins(10, 0, 0, 8);
    m_LabelVersions->setFixedSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    m_LabelVersions->setStyleSheet("QLabel { color: white; }");
    QFont font = loading->font();
    font.setPointSize(10);
    loading->setFont(font);
    m_LabelVersion->setFont(font);
    m_LabelVersions->setFont(font);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    widget->setLayout(layout);
    return widget;
}

void SplashWindow::handleTimerTimeout()
{
    if (mVersionJava.isEmpty()) {
        mVersionJava = "1.9.0";
    } else if (mVersionApktool.isEmpty()) {
        mVersionApktool = "2.3.7";
    } else if (mVersionJadx.isEmpty()) {
        mVersionJadx = "0.9.2";
    } else {
        (new MainWindow())->show();
        close();
        return;
    }
    rewriteVersionsText();
    QTimer::singleShot(1000, this, &SplashWindow::handleTimerTimeout);
}

void SplashWindow::rewriteVersionsText()
{
    QStringList versions;
    versions << QString("<strong>Java</strong>: ").append(mVersionJava);
    versions << QString("<strong>Apktool</strong>: ").append(mVersionApktool);
    versions << QString("<strong>Jadx</strong>: ").append(mVersionJadx);
    m_LabelVersions->setText(versions.join("<br>"));
}

SplashWindow::~SplashWindow()
{
}
