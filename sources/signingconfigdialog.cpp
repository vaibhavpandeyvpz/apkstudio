#include <QVBoxLayout>
#include "signingconfigdialog.h"

SigningConfigDialog::SigningConfigDialog(QWidget *parent)
    : QDialog(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_Widget = new SigningConfigWidget(this));
    layout->addWidget(buildButtonBox());
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(2);
    setMinimumSize(320, 160);
#ifdef Q_OS_WIN
    setWindowIcon(QIcon(":/icons/fugue/edit-signiture.png"));
#endif
    setWindowTitle(tr("Sign APK"));
}

QString SigningConfigDialog::alias() const
{
    return m_Widget->alias();
}

QString SigningConfigDialog::aliasPassword() const
{
    return m_Widget->aliasPassword();
}

QWidget *SigningConfigDialog::buildButtonBox()
{
    m_ButtonBox = new QDialogButtonBox(this);
    m_ButtonBox->addButton(tr("Sign"), QDialogButtonBox::AcceptRole);
    m_ButtonBox->addButton(QDialogButtonBox::Cancel);
    connect(m_ButtonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_ButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    return m_ButtonBox;
}

QString SigningConfigDialog::keystore() const
{
    return m_Widget->keystore();
}

QString SigningConfigDialog::keystorePassword() const
{
    return m_Widget->keystorePassword();
}

bool SigningConfigDialog::zipalign() const
{
    return m_Widget->zipalign();
}
