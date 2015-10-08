#include <QDialogButtonBox>
#include <QDirIterator>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include "pathutils.h"
#include "preopenapk.h"
#include "qrc.h"

AS_NAMESPACE_START

PreOpenApk::PreOpenApk(const QString &a, QWidget *p)
    : Dialog("", p)
{
    QFileInfo fi(a);
    QString project = PathUtils::combine(fi.absolutePath(), fi.completeBaseName());
    setAttribute(Qt::WA_DeleteOnClose, false);
    setFixedSize(360, 180);
    setWindowIcon(Qrc::icon("toolbar_apk"));
    setWindowTitle(Qrc::text("dialog.open_apk.title").arg(fi.fileName()));
    // Form : Start
    QFormLayout *form = new QFormLayout;
    form->addRow(Qrc::text("dialog.open_apk.form.apk_path"), _apk = new QLineEdit(a, this));
    QPushButton *browse = new QPushButton(Qrc::text("dialog.open_apk.buttons.browse"), this);
    QLayout *row = new QHBoxLayout;
    row->addWidget(_project = new QLineEdit(project, this));
    row->addWidget(browse);
    form->addRow(Qrc::text("dialog.open_apk.form.project_path"), row);
    form->addRow(Qrc::text("dialog.open_apk.form.framework_tag"), _framework = new QComboBox(this));
    // Form : End
    QVBoxLayout *layout = new QVBoxLayout(this);
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->addButton(new QPushButton(Qrc::text("dialog.open_apk.buttons.cancel"), buttons), QDialogButtonBox::RejectRole);
    buttons->addButton(new QPushButton(Qrc::text("dialog.open_apk.buttons.decode"), buttons), QDialogButtonBox::AcceptRole);
    layout->addLayout(form);
    layout->addWidget(buttons);
    setLayout(layout);
    _apk->setReadOnly(true);
    _connections << connect(browse, &QPushButton::clicked, [=]
    {
        QString dir;
        QFileInfo fi(project);
        if (fi.exists() && fi.isFile())
        {
            dir = fi.absolutePath();
        }
        QFileDialog d(this, Qrc::text("dialog.open_apk_project.title"), dir);
        d.setFileMode(QFileDialog::Directory);
        d.setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (d.exec() == QFileDialog::Accepted)
        {
            QStringList files;
            if ((files = d.selectedFiles()).isEmpty() == false)
            {
                _project->setText(files.first());
            }
        }
    });
    _connections << connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    _connections << connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::close);
    // List Frameworks
    _framework->addItem("Default");
    QDirIterator iterator(PathUtils::combine(QDir::homePath(), "apktool/framework"), QDirIterator::Subdirectories);
    while (iterator.hasNext())
    {
        QFileInfo file(iterator.next());
        if (file.exists() && file.isFile())
        {
            QString name = file.baseName();
            QStringList parts = name.split(QChar('-')).mid(0, 2);
            if (parts.count() == 2)
            {
                QString tag = name.section('-', 1);
                _framework->addItem(QString("%1 [%2]").arg(parts.at(0)).arg(tag), tag);
            }
        }
    }
}

QString PreOpenApk::framework()
{
    return _framework->currentData().toString();
}

AS_NAMESPACE_END
