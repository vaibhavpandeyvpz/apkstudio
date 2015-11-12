#ifndef SIGNEXPORTAPK_H
#define SIGNEXPORTAPK_H

#include <QLineEdit>
#include "dialog.h"
#include "macros.h"

APP_NAMESPACE_START

class SignExportApk : public Dialog
{
    Q_OBJECT
private:
    QLineEdit *_key;
    QLineEdit *_keyPass;
    QLineEdit *_keystore;
    QLineEdit *_keystorePass;
public:
    explicit SignExportApk(QWidget *parent = 0);
public:
    inline QString key() { return _key->text(); }
    inline QString keyPass() { return _keyPass->text(); }
    inline QString keystore() { return _keystore->text(); }
    inline QString keystorePass() { return _keystorePass->text(); }
private Q_SLOTS:
    void onBrowseKeystore();
    void onSignClicked();
};

APP_NAMESPACE_END

#endif // SIGNEXPORTAPK_H
