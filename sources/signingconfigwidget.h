#ifndef SIGNINGCONFIGWIDGET_H
#define SIGNINGCONFIGWIDGET_H

#include <QCheckBox>
#include <QLineEdit>
#include <QProgressDialog>
#include <QThread>
#include <QWidget>

class KeystoreGenerateDialog;
class KeystoreGenerateWorker;

class SigningConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SigningConfigWidget(QWidget *parent = nullptr);
    QString alias() const;
    QString aliasPassword() const;
    QString keystore() const;
    QString keystorePassword() const;
    bool zipalign() const;
private:
    QLineEdit *m_EditAlias;
    QLineEdit *m_EditAliasPassword;
    QLineEdit *m_EditKeystore;
    QLineEdit *m_EditKeystorePassword;
    QCheckBox *m_CheckZipalign;
    QProgressDialog *m_ProgressDialog;
    QString m_PendingKeystorePassword;
    QString m_PendingAlias;
    QString m_PendingAliasPassword;
    QLayout *buildLayout();
private slots:
    void handleBrowseKeystore();
    void handleGenerateKeystore();
    void handleKeystoreGenerated(const QString &keystorePath);
    void handleKeystoreGenerateFailed(const QString &error);
    void handleKeystoreGenerateFinished();
public slots:
    void save();
};

#endif // SIGNINGCONFIGWIDGET_H
