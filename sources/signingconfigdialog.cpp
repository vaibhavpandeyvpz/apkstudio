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
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumSize(320, 160);
#ifdef Q_OS_WIN
    setWindowIcon(QIcon(":/icons/fugue/edit-signiture.png"));
#endif
    setWindowTitle(tr("Sign APK"));
}

QWidget *SigningConfigDialog::buildButtonBox()
{
    m_ButtonBox = new QDialogButtonBox(this);
    m_ButtonBox->addButton(tr("Sign"), QDialogButtonBox::AcceptRole);
    m_ButtonBox->addButton(QDialogButtonBox::Cancel);
    connect(m_ButtonBox, &QDialogButtonBox::accepted, m_Widget, &SigningConfigWidget::save);
    connect(m_ButtonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_ButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    return m_ButtonBox;
}
