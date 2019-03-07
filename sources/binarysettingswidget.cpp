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
    const QString path = QFileDialog::getOpenFileName(this,
#ifdef Q_OS_WIN
                                                      tr("Browse ADB (adb.exe)"),
#else
                                                      tr("Browse ADB"),
#endif
                                                      QString(),
#ifdef Q_OS_WIN
                                                      tr("Executable File(s) (*.exe)")
#endif
                                                      );
    if (!path.isEmpty()) {
        m_EditAdbExe->setText(QDir::toNativeSeparators(path));
    }
}

void BinarySettingsWidget::handleBrowseApktool()
{
    const QString path = QFileDialog::getOpenFileName(this,
                                                      tr("Browse Apktool (apktool.jar)"),
                                                      QString(),
                                                      tr("JAR File(s) (*.jar)"));
    if (!path.isEmpty()) {
        m_EditApktoolJar->setText(QDir::toNativeSeparators(path));
    }
}

void BinarySettingsWidget::handleBrowseJadx()
{
    const QString path = QFileDialog::getOpenFileName(this,
#ifdef Q_OS_WIN
                                                      tr("Browse Jadx (jadx.bat)"),
#else
                                                      tr("Browse Jadx"),
#endif
                                                      QString(),
#ifdef Q_OS_WIN
                                                      tr("Windows Batch File(s) (*.bat)")
#endif
                                                      );
    if (!path.isEmpty()) {
        m_EditJadxExe->setText(QDir::toNativeSeparators(path));
    }
}

void BinarySettingsWidget::handleBrowseJava()
{
    const QString path = QFileDialog::getOpenFileName(this,
#ifdef Q_OS_WIN
                                                      tr("Browse Java (java.exe)"),
#else
                                                      tr("Browse Java"),
#endif
                                                      QString(),
#ifdef Q_OS_WIN
                                                      tr("Executable File(s) (*.exe)")
#endif
                                                      );
    if (!path.isEmpty()) {
        m_EditJavaExe->setText(QDir::toNativeSeparators(path));
    }
}

void BinarySettingsWidget::handleBrowseUberApkSigner()
{
    const QString path = QFileDialog::getOpenFileName(this,
                                                      tr("Browse Uber APK Signer (uber-apk-signer.jar)"),
                                                      QString(),
                                                      tr("JAR File(s) (*.jar)"));
    if (!path.isEmpty()) {
        m_EditUberApkSignerJar->setText(QDir::toNativeSeparators(path));
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
    m_EditJavaExe->setText(settings.value("java_exe").toString());
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
