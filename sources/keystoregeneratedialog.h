#ifndef KEYSTOREGENERATEDIALOG_H
#define KEYSTOREGENERATEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QLayout>

class KeystoreGenerateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KeystoreGenerateDialog(QWidget *parent = nullptr);
    QString keystorePath() const;
    QString keystorePassword() const;
    QString alias() const;
    QString aliasPassword() const;
    int validity() const;
    QString keyAlgorithm() const;
    int keySize() const;
private:
    QLineEdit *m_EditKeystorePath;
    QLineEdit *m_EditKeystorePassword;
    QLineEdit *m_EditAlias;
    QLineEdit *m_EditAliasPassword;
    QSpinBox *m_SpinValidity;
    QComboBox *m_ComboKeyAlgorithm;
    QSpinBox *m_SpinKeySize;
    QDialogButtonBox *m_ButtonBox;
    QWidget *buildButtonBox();
    QLayout *buildForm();
private slots:
    void handleBrowseKeystore();
    void validateInputs();
};

#endif // KEYSTOREGENERATEDIALOG_H

