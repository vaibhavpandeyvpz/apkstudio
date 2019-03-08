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
    setMinimumSize(320, 160);
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
    layout->addRow(tr("Decompile Java?"), m_CheckSources = new QCheckBox(this));
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
                                                           tr("Browse Output Folder"),
                                                           info.dir().absolutePath(),
                                                           QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);
    if (!path.isEmpty()) {
        m_EditFolder->setText(QDir::toNativeSeparators(path));
    }
}

bool ApkDecompileDialog::sources() const
{
    return m_CheckSources->isChecked();
}
