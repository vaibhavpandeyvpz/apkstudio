#include <QAbstractButton>
#include <QFormLayout>
#include <QIcon>
#include <QSettings>
#include <QVBoxLayout>
#include "binarysettingsdialog.h"

BinarySettingsDialog::BinarySettingsDialog(const QString &focus, QWidget *parent)
    : QDialog(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_Widget = new BinarySettingsWidget(focus, this));
    layout->addWidget(buildButtonBox());
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(2);
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumSize(360, 240);
#ifdef Q_OS_WIN
    setWindowIcon(QIcon(":/icons/fugue/application-terminal.png"));
#endif
    setWindowTitle(tr("Binaries"));
}

QWidget *BinarySettingsDialog::buildButtonBox()
{
    m_ButtonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, this);
    connect(m_ButtonBox, &QDialogButtonBox::clicked, this, &BinarySettingsDialog::handleButtonClick);
    return m_ButtonBox;
}

void BinarySettingsDialog::handleButtonClick(QAbstractButton *button)
{
    if (m_ButtonBox->standardButton(button) == QDialogButtonBox::Save) {
        QSettings settings;
        settings.setValue("apktool_jar", m_Widget->apktoolJar());
        settings.setValue("jadx_exe", m_Widget->jadxExe());
        settings.setValue("java_exe", m_Widget->javaExe());
        settings.sync();
        accept();
    } else {
        reject();
    }
}
