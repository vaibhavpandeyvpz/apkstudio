#include <QDialogButtonBox>
#include <QDirIterator>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include "include/pathutils.h"
#include "include/preopenapk.h"
#include "include/qrc.h"

APP_NAMESPACE_START

PreOpenApk::PreOpenApk(const QString &a, QWidget *p)
    : Dialog(QString(), p)
{
    QFileInfo fi(a);
    QString project = PathUtils::combine(fi.absolutePath(), fi.completeBaseName());
    setAttribute(Qt::WA_DeleteOnClose, false);
#ifdef Q_OS_LINUX
    setFixedSize(480, 192);
#else
    setFixedSize(360, 180);
#endif
    setWindowIcon(Qrc::icon("toolbar_apk"));
    setWindowTitle(__("decode_apk", "titles", fi.fileName()));
    // Form : Start
    QFormLayout *form = new QFormLayout;
    form->addRow(__("apk_path", "forms"), _apk = new QLineEdit(a, this));
    QPushButton *browse = new QPushButton(__("browse", "buttons"), this);
    QLayout *row = new QHBoxLayout;
    row->addWidget(_project = new QLineEdit(project, this));
    row->addWidget(browse);
    form->addRow(__("project_path", "forms"), row);
    form->addRow(__("framework_tag", "forms"), _framework = new QComboBox(this));
    // Form : End
    QVBoxLayout *layout = new QVBoxLayout(this);
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->addButton(new QPushButton(__("cancel", "buttons"), buttons), QDialogButtonBox::RejectRole);
    buttons->addButton(new QPushButton(__("decode", "buttons"), buttons), QDialogButtonBox::AcceptRole);
    layout->addLayout(form);
    layout->addWidget(buttons);
    setLayout(layout);
    _apk->setReadOnly(true);
    _connections << connect(browse, SIGNAL(clicked()), this, SLOT(onBrowseProject()));
    _connections << connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
    _connections << connect(buttons, SIGNAL(rejected()), this, SLOT(close()));
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

void PreOpenApk::onBrowseProject()
{
    QString dir;
    QFileInfo fi(_project->text());
    if (fi.exists() && fi.isFile())
    {
        dir = fi.absolutePath();
    }
    QFileDialog d(this, __("choose_project_directory", "titles"), dir);
    d.setFileMode(QFileDialog::Directory);
    d.setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#ifdef NO_NATIVE_DIALOG
    d.setOption(QFileDialog::DontUseNativeDialog);
#endif
    if (d.exec() == QFileDialog::Accepted)
    {
        QStringList files;
        if ((files = d.selectedFiles()).isEmpty() == false)
        {
            _project->setText(files.first());
        }
    }
}

APP_NAMESPACE_END
