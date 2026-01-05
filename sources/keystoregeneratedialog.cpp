#include <QAbstractButton>
#include <QDir>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include "keystoregeneratedialog.h"

KeystoreGenerateDialog::KeystoreGenerateDialog(QWidget *parent)
    : QDialog(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->addLayout(buildForm());
    layout->addWidget(buildButtonBox());
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(2);
    setMinimumSize(400, 280);
#ifdef Q_OS_WIN
    setWindowIcon(QIcon(":/icons/fugue/edit-signiture.png"));
#endif
    setWindowTitle(tr("Generate Keystore"));
    
    // Initial validation
    validateInputs();
}

QString KeystoreGenerateDialog::keystorePath() const
{
    return m_EditKeystorePath->text();
}

QString KeystoreGenerateDialog::keystorePassword() const
{
    return m_EditKeystorePassword->text();
}

QString KeystoreGenerateDialog::alias() const
{
    return m_EditAlias->text();
}

QString KeystoreGenerateDialog::aliasPassword() const
{
    return m_EditAliasPassword->text();
}

int KeystoreGenerateDialog::validity() const
{
    return m_SpinValidity->value();
}

QString KeystoreGenerateDialog::keyAlgorithm() const
{
    return m_ComboKeyAlgorithm->currentText();
}

int KeystoreGenerateDialog::keySize() const
{
    return m_SpinKeySize->value();
}

QLayout *KeystoreGenerateDialog::buildForm()
{
    auto layout = new QFormLayout();
    
    // Keystore path
    layout->addRow(tr("Keystore Path"), m_EditKeystorePath = new QLineEdit(this));
    m_EditKeystorePath->setPlaceholderText(tr("e.g., /path/to/my.keystore"));
    QPushButton* browseButton = new QPushButton(tr("Browse"), this);
    connect(browseButton, &QPushButton::pressed, this, &KeystoreGenerateDialog::handleBrowseKeystore);
    auto browseLayout = new QHBoxLayout();
    browseLayout->addWidget(browseButton);
    auto empty = new QWidget(this);
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    browseLayout->addWidget(empty);
    layout->addRow("", browseLayout);
    
    // Keystore password
    layout->addRow(tr("Keystore Password"), m_EditKeystorePassword = new QLineEdit(this));
    m_EditKeystorePassword->setEchoMode(QLineEdit::Password);
    m_EditKeystorePassword->setPlaceholderText(tr("Enter keystore password"));
    connect(m_EditKeystorePassword, &QLineEdit::textChanged, this, &KeystoreGenerateDialog::validateInputs);
    
    // Alias
    layout->addRow(tr("Alias"), m_EditAlias = new QLineEdit(this));
    m_EditAlias->setPlaceholderText(tr("e.g., mykey"));
    connect(m_EditAlias, &QLineEdit::textChanged, this, &KeystoreGenerateDialog::validateInputs);
    
    // Alias password
    layout->addRow(tr("Alias Password"), m_EditAliasPassword = new QLineEdit(this));
    m_EditAliasPassword->setEchoMode(QLineEdit::Password);
    m_EditAliasPassword->setPlaceholderText(tr("Enter alias password"));
    connect(m_EditAliasPassword, &QLineEdit::textChanged, this, &KeystoreGenerateDialog::validateInputs);
    
    // Validity (days)
    m_SpinValidity = new QSpinBox(this);
    m_SpinValidity->setMinimum(1);
    m_SpinValidity->setMaximum(99999);
    m_SpinValidity->setValue(10000);
    m_SpinValidity->setSuffix(tr(" days"));
    layout->addRow(tr("Validity"), m_SpinValidity);
    
    // Key algorithm
    m_ComboKeyAlgorithm = new QComboBox(this);
    m_ComboKeyAlgorithm->addItems(QStringList() << "RSA" << "DSA" << "EC");
    layout->addRow(tr("Key Algorithm"), m_ComboKeyAlgorithm);
    
    // Key size
    m_SpinKeySize = new QSpinBox(this);
    m_SpinKeySize->setMinimum(512);
    m_SpinKeySize->setMaximum(16384);
    m_SpinKeySize->setValue(2048);
    m_SpinKeySize->setSingleStep(512);
    m_SpinKeySize->setSuffix(tr(" bits"));
    layout->addRow(tr("Key Size"), m_SpinKeySize);
    
    layout->setSpacing(2);
    return layout;
}

QWidget *KeystoreGenerateDialog::buildButtonBox()
{
    m_ButtonBox = new QDialogButtonBox(this);
    m_ButtonBox->addButton(tr("Generate"), QDialogButtonBox::AcceptRole);
    m_ButtonBox->addButton(QDialogButtonBox::Cancel);
    connect(m_ButtonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_ButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    return m_ButtonBox;
}

void KeystoreGenerateDialog::handleBrowseKeystore()
{
    const QString path = QFileDialog::getSaveFileName(this,
                                                      tr("Save Keystore"),
                                                      QString(),
                                                      tr("Java Keystore (*.keystore *.jks)"));
    if (!path.isEmpty()) {
        m_EditKeystorePath->setText(QDir::toNativeSeparators(path));
        validateInputs();
    }
}

void KeystoreGenerateDialog::validateInputs()
{
    bool valid = !m_EditKeystorePath->text().isEmpty() &&
                 !m_EditKeystorePassword->text().isEmpty() &&
                 !m_EditAlias->text().isEmpty() &&
                 !m_EditAliasPassword->text().isEmpty();
    
    QList<QAbstractButton *> buttons = m_ButtonBox->buttons();
    for (QAbstractButton *button : buttons) {
        if (m_ButtonBox->buttonRole(button) == QDialogButtonBox::AcceptRole) {
            button->setEnabled(valid);
            break;
        }
    }
}

