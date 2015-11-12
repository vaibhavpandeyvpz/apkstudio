#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include "include/preferences.h"
#include "include/runner.h"
#include "include/signexportapk.h"
#include "include/qrc.h"

APP_NAMESPACE_START

SignExportApk::SignExportApk(QWidget *p)
    : Dialog(__("sign_export", "titles"), p)
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    setFixedSize(360, 180);
    setWindowIcon(Qrc::icon("toolbar_sign"));
    Preferences *pr = Preferences::get();
    // Form : Start
    QFormLayout *form = new QFormLayout;
    QPushButton *browse = new QPushButton(__("browse", "buttons"), this);
    QLayout *row = new QHBoxLayout;
    row->addWidget(_keystore = new QLineEdit(pr->signKeystore(), this));
    row->addWidget(browse);
    form->addRow(__("keystore", "forms"), row);
    form->addRow(__("keystore_pass", "forms"), _keystorePass = new QLineEdit(pr->signKeystorePass(), this));
    form->addRow(__("key", "forms"), _key = new QLineEdit(pr->signKey(), this));
    form->addRow(__("key_pass", "forms"), _keyPass = new QLineEdit(pr->signKeyPass(), this));
    _keyPass->setEchoMode(QLineEdit::Password);
    _keystorePass->setEchoMode(QLineEdit::Password);
    // Form : End
    QVBoxLayout *layout = new QVBoxLayout(this);
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->addButton(new QPushButton(__("cancel", "buttons"), buttons), QDialogButtonBox::RejectRole);
    buttons->addButton(new QPushButton(__("sign", "buttons"), buttons), QDialogButtonBox::AcceptRole);
    layout->addLayout(form);
    layout->addWidget(buttons);
    _connections << connect(browse, SIGNAL(clicked()), this, SLOT(onBrowseKeystore()));
    _connections << connect(buttons, SIGNAL(accepted()), this, SLOT(onSignClicked()));
    _connections << connect(buttons, SIGNAL(rejected()), this, SLOT(close()));
}

void SignExportApk::onBrowseKeystore()
{
    QString dir;
    QFileInfo fi(_keystore->text());
    if (fi.exists() && fi.isFile())
    {
        dir = fi.absolutePath();
    }
    QFileDialog d(this, __("choose_keystore", "titles"), dir);
    d.setAcceptMode(QFileDialog::AcceptOpen);
    d.setFileMode(QFileDialog::ExistingFile);
#ifdef NO_NATIVE_DIALOG
    d.setOption(QFileDialog::DontUseNativeDialog);
#endif
    if (d.exec() == QFileDialog::Accepted)
    {
        QStringList files;
        if ((files = d.selectedFiles()).isEmpty() == false)
        {
            _keystore->setText(files.first());
        }
    }
}

void SignExportApk::onSignClicked()
{
    Preferences::get()
            ->setSignKey(_key->text())
            ->setSignKeyPass(_keyPass->text())
            ->setSignKeystore(_keystore->text())
            ->setSignKeystorePass(_keystorePass->text())
            ->save();
    Dialog::accept();
}

APP_NAMESPACE_END
