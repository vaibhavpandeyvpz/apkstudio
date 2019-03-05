#include <QDebug>
#include <QPixmap>
#include <QVBoxLayout>
#include <QTimer>
#include "binarysettingsdialog.h"
#include "mainwindow.h"
#include "processutils.h"
#include "splashwindow.h"

#define SPLASH_WIDTH 512
#define SPLASH_HEIGHT 320

SplashWindow::SplashWindow()
    : QMainWindow(nullptr, Qt::FramelessWindowHint)
{
    setCentralWidget(buildCentralWidget());
    setMaximumSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    setMinimumSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    QTimer::singleShot(500, this, &SplashWindow::resolveVersions);
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
    auto version = new QLabel(widget);
    version->setAlignment(Qt::AlignRight);
    version->setContentsMargins(0, 2, 4, 0);
    version->setFixedSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    version->setStyleSheet("QLabel { color: white; }");
    if (QString(GIT_TAG).isEmpty()) {
        version->setText(QString("%1.%2").arg(GIT_COMMIT_SHORT).arg(GIT_COMMIT_NUMBER));
    } else {
        version->setText(GIT_TAG);
    }
    m_LabelVersions = new QLabel(widget);
    m_LabelVersions->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    m_LabelVersions->setContentsMargins(10, 0, 0, 8);
    m_LabelVersions->setFixedSize(SPLASH_WIDTH, SPLASH_HEIGHT);
    m_LabelVersions->setStyleSheet("QLabel { color: white; }");
    QFont font = loading->font();
    font.setPointSize(10);
    loading->setFont(font);
    version->setFont(font);
    m_LabelVersions->setFont(font);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    widget->setLayout(layout);
    return widget;
}

void SplashWindow::handleVersionFailed(const QString &binary)
{
#ifdef QT_DEBUG
    qDebug() << "Binary" << binary << "version resolution failed";
#endif
    auto dialog = new BinarySettingsDialog(binary, this);
    connect(dialog, &QDialog::accepted, this, &SplashWindow::resolveVersions);
    connect(dialog, &QDialog::rejected, this, &QMainWindow::close);
    QTimer::singleShot(100, dialog, &QDialog::exec);
}

void SplashWindow::handleVersionResolved(const QString &binary, const QString &version)
{
#ifdef QT_DEBUG
    qDebug() << "Binary" << binary << "version resolved as" << version;
#endif
    if (binary == "apktool") {
        mVersionApktool = version;
    } else if (binary == "jadx") {
        mVersionJadx = version;
    } else if (binary == "java") {
        mVersionJava = version;
    }
    rewriteVersionsText();
}

void SplashWindow::handleVersionSuccess()
{
    QTimer::singleShot(1000, [=] {
        (new MainWindow())->show();
        close();
    });
}

void SplashWindow::resolveVersions()
{
    m_VersionsThread = new BinaryVersionsThread();
    connect(m_VersionsThread, &BinaryVersionsThread::versionFailed, this, &SplashWindow::handleVersionFailed);
    connect(m_VersionsThread, &BinaryVersionsThread::versionResolved, this, &SplashWindow::handleVersionResolved);
    connect(m_VersionsThread, &BinaryVersionsThread::versionSuccess, this, &SplashWindow::handleVersionSuccess);
    connect(m_VersionsThread, &BinaryVersionsThread::finished, m_VersionsThread, &QObject::deleteLater);
    m_VersionsThread->start();
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
