#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QIcon>
#include <QPushButton>
#include "qrc.h"
#include "preferences.h"
#include "settingseditor.h"

AS_NAMESPACE_START

SettingsEditor::SettingsEditor(QWidget *p)
    : Dialog(Qrc::text("dialog.settings.title"), p)
{
    setFixedSize(480, 192);
    setWindowIcon(Qrc::icon("toolbar_settings"));
    auto pr = Preferences::get();
    // Form : Start
    QFormLayout *form = new QFormLayout;
    QPushButton *browse = new QPushButton(Qrc::text("dialog.settings.buttons.browse"), this);
    QLayout *row = new QHBoxLayout;
    row->addWidget(_binariesPath = new QLineEdit(pr->binariesPath(), this));
    row->addWidget(browse);
    form->addRow(Qrc::text("dialog.settings.form.binaries_path"), row);
    _javaHeap = new QSpinBox(this);
    _javaHeap->setMinimum(16);
    _javaHeap->setMaximum(4096);
    _javaHeap->setSingleStep(4);
    _javaHeap->setValue(pr->javaHeap());
    form->addRow(Qrc::text("dialog.settings.form.java_heap"), _javaHeap);
    form->addRow(Qrc::text("dialog.settings.form.show_whitespaces"), _showWhitespaces = new QCheckBox(this));
    _tabStopWidth = new QSpinBox(this);
    _tabStopWidth->setMinimum(1);
    _tabStopWidth->setMaximum(99);
    _tabStopWidth->setSingleStep(1);
    _tabStopWidth->setValue(pr->tabStopWidth());
    form->addRow(Qrc::text("dialog.settings.form.tab_stop_width"), _tabStopWidth);
    form->addRow(Qrc::text("dialog.settings.form.spaces_for_tabs"), _useSpacesForTabs = new QCheckBox(this));
    _showWhitespaces->setChecked(pr->showWhitespaces());
    _useSpacesForTabs->setChecked(pr->useSpacesForTabs());
    // Form : End
    QVBoxLayout *layout = new QVBoxLayout(this);
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->addButton(new QPushButton(Qrc::text("dialog.settings.buttons.cancel"), buttons), QDialogButtonBox::RejectRole);
    buttons->addButton(new QPushButton(Qrc::text("dialog.settings.buttons.save"), buttons), QDialogButtonBox::AcceptRole);
    layout->addLayout(form);
    layout->addWidget(buttons);
    _connections << connect(browse, &QPushButton::clicked, [=]
    {
        QFileDialog d(this, Qrc::text("dialog.open.binaries.title"), pr->binariesPath());
        d.setAcceptMode(QFileDialog::AcceptOpen);
        d.setFileMode(QFileDialog::Directory);
        d.setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (d.exec() == QFileDialog::Accepted)
        {
            QStringList files;
            if ((files = d.selectedFiles()).isEmpty() == false)
            {
                _binariesPath->setText(files.first());
            }
        }
    });
    _connections << connect(buttons, &QDialogButtonBox::accepted, this, &SettingsEditor::onSaveClicked);
    _connections << connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::close);
}

void SettingsEditor::onSaveClicked()
{
    Preferences::get()
            ->setBinariesPath(_binariesPath->text())
            ->setJavaHeap(_javaHeap->value())
            ->setShowWhitespaces(_showWhitespaces->isChecked())
            ->setTabStopWidth(_tabStopWidth->value())
            ->setUseSpacesForTabs(_useSpacesForTabs->isChecked())
            ->save();
    close();
}

AS_NAMESPACE_END
