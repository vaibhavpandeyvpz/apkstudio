#include <QDir>
#include <QFileDialog>
#include <QFormLayout>
#include <QPushButton>
#include <QSettings>
#include "signingconfigwidget.h"

SigningConfigWidget::SigningConfigWidget(QWidget *parent)
    : QWidget(parent)
{
    setLayout(buildLayout());
    m_EditKeystore->selectAll();
    m_EditKeystore->setFocus();
}

QString SigningConfigWidget::alias() const
{
    return m_EditAlias->text();
}

QString SigningConfigWidget::aliasPassword() const
{
    return m_EditAliasPassword->text();
}

QLayout *SigningConfigWidget::buildLayout()
{
    auto layout = new QFormLayout(this);
    layout->addRow(tr("Keystore"), m_EditKeystore = new QLineEdit(this));
    QPushButton* button;
    QHBoxLayout* child = new QHBoxLayout();
    child->addWidget(button = new QPushButton(tr("Browse"), this));
    connect(button, &QPushButton::pressed, this, &SigningConfigWidget::handleBrowseKeystore);
    auto empty = new QWidget(this);
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    child->addWidget(empty);
    layout->addRow("", child);
    layout->addRow(tr("Keystore Password"), m_EditKeystorePassword = new QLineEdit(this));
    m_EditKeystorePassword->setEchoMode(QLineEdit::Password);
    layout->addRow(tr("Alias"), m_EditAlias = new QLineEdit(this));
    layout->addRow(tr("Alias Password"), m_EditAliasPassword = new QLineEdit(this));
    m_EditAliasPassword->setEchoMode(QLineEdit::Password);
    layout->addRow(tr("Zipalign?"), m_CheckZipalign = new QCheckBox(this));
    QSettings settings;
    m_EditKeystore->setText(settings.value("signing_keystore").toString());
    m_EditKeystorePassword->setText(settings.value("signing_keystore_password").toString());
    m_EditAlias->setText(settings.value("signing_alias").toString());
    m_EditAliasPassword->setText(settings.value("signing_alias_password").toString());
    m_CheckZipalign->setChecked(settings.value("signing_zipalign", true).toBool());
    return layout;
}

void SigningConfigWidget::handleBrowseKeystore()
{
    const QString path = QFileDialog::getOpenFileName(this, tr("Browse Java Keystore"));
    if (!path.isEmpty()) {
        m_EditKeystore->setText(QDir::toNativeSeparators(path));
    }
}

void SigningConfigWidget::save()
{
    QSettings settings;
    settings.setValue("signing_keystore", m_EditKeystore->text());
    settings.setValue("signing_keystore_password", m_EditKeystorePassword->text());
    settings.setValue("signing_alias", m_EditAlias->text());
    settings.setValue("signing_alias_password", m_EditAliasPassword->text());
    settings.setValue("signing_zipalign", m_CheckZipalign->isChecked());
    settings.sync();
}

QString SigningConfigWidget::keystore() const
{
    return m_EditKeystore->text();
}

QString SigningConfigWidget::keystorePassword() const
{
    return m_EditKeystorePassword->text();
}

bool SigningConfigWidget::zipalign() const
{
    return m_CheckZipalign->isChecked();
}
