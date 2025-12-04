#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include "apkdecompiledialog.h"

ApkDecompileDialog::ApkDecompileDialog(const QString &apk, QWidget *parent)
    : QDialog(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->addLayout(buildForm(apk));
    layout->addWidget(buildButtonBox());
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(2);
    setMinimumSize(340, 160);
#ifdef Q_OS_WIN
    setWindowIcon(QIcon(":/icons/fugue/android.png"));
#endif
    setWindowTitle(tr("Open APK"));
}

QString ApkDecompileDialog::apk() const
{
    return m_EditApk->text();
}

QWidget *ApkDecompileDialog::buildButtonBox()
{
    m_ButtonBox = new QDialogButtonBox(this);
    m_ButtonBox->addButton(tr("Decompile"), QDialogButtonBox::AcceptRole);
    m_ButtonBox->addButton(QDialogButtonBox::Cancel);
    connect(m_ButtonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_ButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    return m_ButtonBox;
}

QLayout *ApkDecompileDialog::buildForm(const QString &apk)
{
    auto layout = new QFormLayout();
    layout->addRow(tr("APK"), m_EditApk = new QLineEdit(apk, this));
    m_EditApk->setDisabled(true);
    layout->addRow(tr("Output"), m_EditFolder = new QLineEdit(this));
    m_EditFolder->setText(QString(apk).append("-decompiled"));
    auto button = new QPushButton(tr("Browse"), this);
    connect(button, &QPushButton::pressed, this, &ApkDecompileDialog::handleBrowseFolder);
    auto child = new QHBoxLayout();
    child->addWidget(button);
    auto empty = new QWidget(this);
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    child->addWidget(empty);
    layout->addRow("", child);
    layout->addRow(tr("Decompile smali?"), m_CheckSmali = new QCheckBox(this));
    m_CheckSmali->setChecked(true);
    layout->addRow(tr("Decompile resources?"), m_CheckResources = new QCheckBox(this));
    m_CheckResources->setChecked(true);
    layout->addRow(tr("Decompile java?"), m_CheckJava = new QCheckBox(this));
    layout->addRow(tr("Framework tag (optional)"), m_EditFrameworkTag = new QLineEdit(this));
    m_EditFrameworkTag->setPlaceholderText(tr("e.g., hero, desire, samsung"));
    m_EditFrameworkTag->setToolTip(tr("Specify a framework tag if you installed frameworks with a tag. Leave empty to use default framework."));
    layout->setSpacing(2);
    return layout;
}

QString ApkDecompileDialog::folder() const
{
    return m_EditFolder->text();
}

void ApkDecompileDialog::handleBrowseFolder()
{
    QFileInfo info(m_EditApk->text());
    const QString path = QFileDialog::getExistingDirectory(this,
                                                           tr("Browse output folder"),
                                                           info.dir().absolutePath(),
                                                           QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);
    if (!path.isEmpty()) {
        m_EditFolder->setText(QDir::toNativeSeparators(path));
    }
}

bool ApkDecompileDialog::java() const
{
    return m_CheckJava->isChecked();
}

bool ApkDecompileDialog::resources() const
{
    return m_CheckResources->isChecked();
}

bool ApkDecompileDialog::smali() const
{
    return m_CheckSmali->isChecked();
}

QString ApkDecompileDialog::frameworkTag() const
{
    return m_EditFrameworkTag->text().trimmed();
}
