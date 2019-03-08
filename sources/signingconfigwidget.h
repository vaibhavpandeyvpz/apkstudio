#ifndef SIGNINGCONFIGWIDGET_H
#define SIGNINGCONFIGWIDGET_H

#include <QCheckBox>
#include <QLineEdit>
#include <QWidget>

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
    QLayout *buildLayout();
private slots:
    void handleBrowseKeystore();
};

#endif // SIGNINGCONFIGWIDGET_H
