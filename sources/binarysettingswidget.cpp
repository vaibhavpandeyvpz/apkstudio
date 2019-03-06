#include <QDir>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include "binarysettingswidget.h"
#include "processutils.h"

BinarySettingsWidget::BinarySettingsWidget(const QString &focus, QWidget *parent)
    : QWidget(parent)
{
    setLayout(buildForm());
    if (focus == "adb") {
        m_EditAdbExe->selectAll();
        m_EditAdbExe->setFocus();
    } else if (focus == "apktool") {
        m_EditApktoolJar->selectAll();
        m_EditApktoolJar->setFocus();
    } else if (focus == "jadx") {
        m_EditJadxExe->selectAll();
        m_EditJadxExe->setFocus();
    } else if (focus == "java") {
        m_EditJavaExe->selectAll();
        m_EditJavaExe->setFocus();
    } else if (focus == "uas") {
        m_EditUberApkSignerJar->selectAll();
        m_EditUberApkSignerJar->setFocus();
    }
}

QString BinarySettingsWidget::adbExe() const
{
    return m_EditAdbExe->text();
}

QString BinarySettingsWidget::apktoolJar() const
{
    return m_EditApktoolJar->text();
}

void BinarySettingsWidget::handleBrowseAdb()
{
#ifdef Q_OS_WIN
    QFileDialog dialog(this, tr("Browse ADB (adb.exe)"), QString(), tr("Executable File(s) (*.exe)"));
#else
    QFileDialog dialog(this, tr("Browse ADB"));
#endif
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec() == QFileDialog::Accepted) {
        const QString path = QDir::toNativeSeparators(dialog.selectedFiles().first());
        m_EditAdbExe->setText(path);
    }
}

void BinarySettingsWidget::handleBrowseApktool()
{
    QFileDialog dialog(this, tr("Browse Apktool (apktool.jar)"), QString(), tr("JAR File(s) (*.jar)"));
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec() == QFileDialog::Accepted) {
        const QString path = QDir::toNativeSeparators(dialog.selectedFiles().first());
        m_EditApktoolJar->setText(path);
    }
}

void BinarySettingsWidget::handleBrowseJadx()
{
#ifdef Q_OS_WIN
    QFileDialog dialog(this, tr("Browse Jadx (jadx.bat)"), QString(), tr("Batch File(s) (*.bat)"));
#else
    QFileDialog dialog(this, tr("Browse Jadx"));
#endif
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec() == QFileDialog::Accepted) {
        const QString path = QDir::toNativeSeparators(dialog.selectedFiles().first());
        m_EditJadxExe->setText(path);
    }
}

void BinarySettingsWidget::handleBrowseJava()
{
#ifdef Q_OS_WIN
    QFileDialog dialog(this, tr("Browse Java (java.exe)"), QString(), tr("Executable File(s) (*.exe)"));
#else
    QFileDialog dialog(this, tr("Browse Java"));
#endif
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec() == QFileDialog::Accepted) {
        const QString path = QDir::toNativeSeparators(dialog.selectedFiles().first());
        m_EditJadxExe->setText(path);
    }
}

void BinarySettingsWidget::handleBrowseUberApkSigner()
{
    QFileDialog dialog(this, tr("Browse Uber APK Signer (uber-apk-signer.jar)"), QString(), tr("JAR File(s) (*.jar)"));
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec() == QFileDialog::Accepted) {
        const QString path = QDir::toNativeSeparators(dialog.selectedFiles().first());
        m_EditUberApkSignerJar->setText(path);
    }
}

QLayout *BinarySettingsWidget::buildForm()
{
    auto layout = new QFormLayout();
    layout->addRow(tr("Java"), m_EditJavaExe = new QLineEdit(this));
    QLabel* label;
    QPushButton* button;
    QHBoxLayout* child = new QHBoxLayout();
    child->addWidget(button = new QPushButton(tr("Browse"), this));
    connect(button, &QPushButton::pressed, this, &BinarySettingsWidget::handleBrowseJava);
    child->addWidget(label = new QLabel(QString("<a href=\"https://www.oracle.com/technetwork/java/javase/downloads/index.html\">%1</a>").arg(tr("Get it here!")), this), 1);
    label->setOpenExternalLinks(true);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setTextFormat(Qt::RichText);
    layout->addRow("", child);
    layout->addRow(tr("Apktool"), m_EditApktoolJar = new QLineEdit(this));
    child = new QHBoxLayout();
    child->addWidget(button = new QPushButton(tr("Browse"), this));
    connect(button, &QPushButton::pressed, this, &BinarySettingsWidget::handleBrowseApktool);
    child->addWidget(label = new QLabel(QString("<a href=\"https://github.com/iBotPeaches/Apktool/releases\">%1</a>").arg(tr("Get it here!")), this), 1);
    label->setOpenExternalLinks(true);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setTextFormat(Qt::RichText);
    layout->addRow("", child);
    layout->addRow(tr("Jadx"), m_EditJadxExe = new QLineEdit(this));
    child = new QHBoxLayout();
    child->addWidget(button = new QPushButton(tr("Browse"), this));
    connect(button, &QPushButton::pressed, this, &BinarySettingsWidget::handleBrowseJadx);
    child->addWidget(label = new QLabel(QString("<a href=\"https://github.com/skylot/jadx/releases\">%1</a>").arg(tr("Get it here!")), this), 1);
    label->setOpenExternalLinks(true);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setTextFormat(Qt::RichText);
    layout->addRow("", child);
    layout->addRow(tr("ADB"), m_EditAdbExe = new QLineEdit(this));
    child = new QHBoxLayout();
    child->addWidget(button = new QPushButton(tr("Browse"), this));
    connect(button, &QPushButton::pressed, this, &BinarySettingsWidget::handleBrowseAdb);
    child->addWidget(label = new QLabel(QString("<a href=\"https://developer.android.com/studio/releases/platform-tools\">%1</a>").arg(tr("Get it here!")), this), 1);
    label->setOpenExternalLinks(true);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setTextFormat(Qt::RichText);
    layout->addRow("", child);
    layout->addRow(tr("Uber APK Signer"), m_EditUberApkSignerJar = new QLineEdit(this));
    child = new QHBoxLayout();
    child->addWidget(button = new QPushButton(tr("Browse"), this));
    connect(button, &QPushButton::pressed, this, &BinarySettingsWidget::handleBrowseUberApkSigner);
    child->addWidget(label = new QLabel(QString("<a href=\"https://github.com/patrickfav/uber-apk-signer/releases\">%1</a>").arg(tr("Get it here!")), this), 1);
    label->setOpenExternalLinks(true);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setTextFormat(Qt::RichText);
    layout->addRow("", child);
    QSettings settings;
    m_EditAdbExe->setText(settings.value("adb_exe").toString());
    m_EditApktoolJar->setText(settings.value("apktool_jar").toString());
    m_EditJadxExe->setText(settings.value("jadx_exe").toString());
    m_EditJavaExe->setText(ProcessUtils::javaExe());
    m_EditUberApkSignerJar->setText(settings.value("uas_jar").toString());
    return layout;
}

QString BinarySettingsWidget::jadxExe() const
{
    return m_EditJadxExe->text();
}

QString BinarySettingsWidget::javaExe() const
{
    return m_EditJavaExe->text();
}

QString BinarySettingsWidget::uberApkSignerJar() const
{
    return m_EditUberApkSignerJar->text();
}
