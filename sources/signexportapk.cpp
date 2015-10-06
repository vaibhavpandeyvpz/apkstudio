#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include "preferences.h"
#include "runner.h"
#include "signexportapk.h"
#include "qrc.h"

AS_NAMESPACE_START

SignExportApk::SignExportApk(QWidget *p)
    : Dialog(Qrc::text("dialog.sign_apk.title"), p)
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    setFixedSize(360, 180);
    setWindowIcon(Qrc::icon("toolbar_sign"));
    auto pr = Preferences::get();
    // Form : Start
    QFormLayout *form = new QFormLayout;
    QPushButton *browse = new QPushButton(Qrc::text("dialog.sign_apk.buttons.browse"), this);
    QLayout *row = new QHBoxLayout;
    row->addWidget(_keystore = new QLineEdit(pr->signKeystore(), this));
    row->addWidget(browse);
    form->addRow(Qrc::text("dialog.sign_apk.form.keystore"), row);
    form->addRow(Qrc::text("dialog.sign_apk.form.keystore_pass"), _keystorePass = new QLineEdit(pr->signKeystorePass(), this));
    form->addRow(Qrc::text("dialog.sign_apk.form.key"), _key = new QLineEdit(pr->signKey(), this));
    form->addRow(Qrc::text("dialog.sign_apk.form.key_pass"), _keyPass = new QLineEdit(pr->signKeyPass(), this));
    // Form : End
    QVBoxLayout *layout = new QVBoxLayout(this);
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->addButton(new QPushButton(Qrc::text("dialog.sign_apk.buttons.cancel"), buttons), QDialogButtonBox::RejectRole);
    buttons->addButton(new QPushButton(Qrc::text("dialog.sign_apk.buttons.sign"), buttons), QDialogButtonBox::AcceptRole);
    layout->addLayout(form);
    layout->addWidget(buttons);
    _connections << connect(browse, &QPushButton::clicked, [=]
    {
        QString dir;
        QFileInfo fi(pr->signKeystore());
        if (fi.exists() && fi.isFile())
        {
            dir = fi.absolutePath();
        }
        QFileDialog d(this, Qrc::text("dialog.open.keystore.title"), dir);
        d.setAcceptMode(QFileDialog::AcceptOpen);
        d.setFileMode(QFileDialog::ExistingFile);
        if (d.exec() == QFileDialog::Accepted)
        {
            QStringList files;
            if ((files = d.selectedFiles()).isEmpty() == false)
            {
                _keystore->setText(files.first());
            }
        }
    });
    _connections << connect(buttons, &QDialogButtonBox::accepted, this, &SignExportApk::onSignClicked);
    _connections << connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::close);
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

AS_NAMESPACE_END
