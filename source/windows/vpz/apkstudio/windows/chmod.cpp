#include "chmod.hpp"

using namespace VPZ::APKStudio::Helpers;
using namespace VPZ::APKStudio::Resources;

namespace VPZ {
namespace APKStudio {
namespace Windows {

CHMOD::CHMOD(const QString &device, const File &file, QWidget *parent) :
    Dialog(parent), device(device), file(file)
{
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    QFormLayout *form = new QFormLayout();
    QGroupBox *group = new QGroupBox(translate("label_group"), this);
    QLineEdit *groupe = new QLineEdit(this);
    QVBoxLayout *groupl = new QVBoxLayout(group);
    QCheckBox *groupr = new QCheckBox(translate("label_read"), group);
    QCheckBox *groupw = new QCheckBox(translate("label_write"), group);
    QCheckBox *groupx = new QCheckBox(translate("label_execute"), group);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLineEdit *ownere = new QLineEdit(this);
    QGroupBox *owner = new QGroupBox(translate("label_owner"), this);
    QVBoxLayout *ownerl = new QVBoxLayout(owner);
    QCheckBox *ownerr = new QCheckBox(translate("label_read"), owner);
    QCheckBox *ownerw = new QCheckBox(translate("label_write"), owner);
    QCheckBox *ownerx = new QCheckBox(translate("label_execute"), owner);
    QHBoxLayout *permissions = new QHBoxLayout();
    QCheckBox *recursive = new QCheckBox(translate("label_recursive"), this);
    QGroupBox *world = new QGroupBox(translate("label_world"), this);
    QVBoxLayout *worldl = new QVBoxLayout(world);
    QCheckBox *worldr = new QCheckBox(translate("label_read"), world);
    QCheckBox *worldw = new QCheckBox(translate("label_write"), world);
    QCheckBox *worldx = new QCheckBox(translate("label_execute"), world);
    buttons->addButton(QDialogButtonBox::Cancel);
    buttons->addButton(QDialogButtonBox::Save);
    connections.append(connect(buttons, SIGNAL(rejected()), this, SLOT(reject())));
    connections.append(connect(buttons, &QDialogButtonBox::accepted, [ groupe, groupr, groupw, groupx, ownere, ownerr, ownerw, ownerx, recursive, worldr, worldw, worldx, this ] () {
        QString group = groupe->text();
        QString mode("0");
        QString owner = ownere->text();
        bool sgroupr = groupr->isChecked();
        bool sgroupw = groupw->isChecked();
        bool sgroupx = groupx->isChecked();
        bool sownerr = ownerr->isChecked();
        bool sownerw = ownerw->isChecked();
        bool sownerx = ownerx->isChecked();
        bool sworldr = worldr->isChecked();
        bool sworldw = worldw->isChecked();
        bool sworldx = worldx->isChecked();
        if (sownerr && sownerw && sownerx)
            mode.append("7");
        else if (sownerr && sownerw)
            mode.append("6");
        else if (sownerr && sownerx)
            mode.append("5");
        else if (sownerr)
            mode.append("4");
        else if (sownerw && sownerx)
            mode.append("3");
        else if (sownerw)
            mode.append("2");
        else if (sownerx)
            mode.append("1");
        else
            mode.append("0");
        if (sgroupr && sgroupw && sgroupx)
            mode.append("7");
        else if (sgroupr && sgroupw)
            mode.append("6");
        else if (sgroupr && sgroupx)
            mode.append("5");
        else if (sgroupr)
            mode.append("4");
        else if (sgroupw && sgroupx)
            mode.append("3");
        else if (sgroupw)
            mode.append("2");
        else if (sgroupx)
            mode.append("1");
        else
            mode.append("0");
        if (sworldr && sworldw && sworldx)
            mode.append("7");
        else if (sworldr && sworldw)
            mode.append("6");
        else if (sworldr && sworldx)
            mode.append("5");
        else if (sworldr)
            mode.append("4");
        else if (sworldw && sworldx)
            mode.append("3");
        else if (sworldw)
            mode.append("2");
        else if (sworldx)
            mode.append("1");
        else
            mode.append("0");
        if (ADB::instance()->chmod(this->device, this->file.path, mode, recursive->isChecked())) {
            if ((QString::compare(group, this->file.group) != 0) || (QString::compare(owner, this->file.owner) != 0)) {
                if (!ADB::instance()->chown(this->device, this->file.path, owner, group, recursive->isChecked()))
                    QMessageBox::critical(this, translate("title_failure"), translate("message_chown_failure").arg(this->file.path, owner, group), QMessageBox::Close);
            }
        } else
            QMessageBox::critical(this, translate("title_failure"), translate("message_chmod_failure").arg(this->file.path, mode), QMessageBox::Close);
        accept();
    }));
    form->addRow(translate("label_owner"), ownere);
    form->addRow(translate("label_group"), groupe);
    groupr->setChecked(file.permission.group.read);
    groupw->setChecked(file.permission.group.write);
    groupx->setChecked(file.permission.group.execute);
    group->setLayout(groupl);
    groupe->setText(file.group);
    groupl->addWidget(groupr);
    groupl->addWidget(groupw);
    groupl->addWidget(groupx);
    owner->setLayout(ownerl);
    ownere->setText(file.owner);
    ownerl->addWidget(ownerr);
    ownerl->addWidget(ownerw);
    ownerl->addWidget(ownerx);
    ownerr->setChecked(file.permission.owner.read);
    ownerw->setChecked(file.permission.owner.write);
    ownerx->setChecked(file.permission.owner.execute);
    recursive->setChecked((file.type == File::FOLDER) || (file.type == File::SYMLINK_FOLDER));
    world->setLayout(worldl);
    worldl->addWidget(worldr);
    worldl->addWidget(worldw);
    worldl->addWidget(worldx);
    worldr->setChecked(file.permission.world.read);
    worldw->setChecked(file.permission.world.write);
    worldx->setChecked(file.permission.world.execute);
    permissions->addWidget(owner);
    permissions->addWidget(group);
    permissions->addWidget(world);
    layout->addLayout(permissions);
    layout->addLayout(form);
    layout->addWidget(recursive);
    layout->addWidget(buttons);
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(4);
    setLayout(layout);
    setMinimumSize(320, 160);
    setWindowIcon(::icon("key_solid"));
    setWindowTitle(translate("title_window").arg(file.name));
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ
