#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QIcon>
#include <QPushButton>
#include <QTextCodec>
#include "include/qrc.h"
#include "include/preferences.h"
#include "include/settingseditor.h"

APP_NAMESPACE_START

SettingsEditor::SettingsEditor(QWidget *p)
    : Dialog(__("settings", "titles"), p)
{
#ifdef Q_OS_WIN
    setFixedSize(480, 192);
#else
    setFixedSize(480, 240);
#endif
    setWindowIcon(Qrc::icon("toolbar_settings"));
    Preferences *pr = Preferences::get();
    // Form : Start
    QFormLayout *form = new QFormLayout;
    QPushButton *browse = new QPushButton(__("browse", "buttons"), this);
    QLayout *row = new QHBoxLayout;
    row->addWidget(_vendorPath = new QLineEdit(pr->vendorPath(), this));
    row->addWidget(browse);
    form->addRow(__("vendor_path", "forms"), row);
    form->addRow(__("java_heap", "forms"), _javaHeap = new QSpinBox(this));
    _javaHeap->setMinimum(16);
    _javaHeap->setMaximum(4096);
    _javaHeap->setSingleStep(4);
    _javaHeap->setValue(pr->javaHeap());
    form->addRow(__("show_whitespaces", "forms"), _showWhitespaces = new QCheckBox(this));
    form->addRow(__("tab_stop_width", "forms"), _tabStopWidth = new QSpinBox(this));
    _tabStopWidth->setMinimum(1);
    _tabStopWidth->setMaximum(99);
    _tabStopWidth->setSingleStep(1);
    _tabStopWidth->setValue(pr->tabStopWidth());
    form->addRow(__("text_encoding", "forms"), _textEncoding = new QComboBox(this));
    QList<int> mibs = QTextCodec::availableMibs();
    foreach (const int mib, mibs)
    {
        QTextCodec *codec = QTextCodec::codecForMib(mib);
        _textEncoding->addItem(codec->name(), codec->mibEnum());
    }
    _textEncoding->setCurrentIndex(_textEncoding->findData(pr->textEncoding()));
    form->addRow(__("use_spaces_for_tabs", "forms"), _useSpacesForTabs = new QCheckBox(this));
    _showWhitespaces->setChecked(pr->showWhitespaces());
    _useSpacesForTabs->setChecked(pr->useSpacesForTabs());
    // Form : End
    QVBoxLayout *layout = new QVBoxLayout(this);
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->addButton(new QPushButton(__("cancel", "buttons"), buttons), QDialogButtonBox::RejectRole);
    buttons->addButton(new QPushButton(__("save", "buttons"), buttons), QDialogButtonBox::AcceptRole);
    layout->addLayout(form);
    layout->addWidget(buttons);
    _connections << connect(browse, SIGNAL(clicked()), this, SLOT(onBrowseVendor()));
    _connections << connect(buttons, SIGNAL(accepted()), this, SLOT(onSaveClicked()));
    _connections << connect(buttons, SIGNAL(rejected()), this, SLOT(close()));
}

void SettingsEditor::onBrowseVendor()
{
    QFileDialog d(this, __("choose_vendor_path", "titles"), _vendorPath->text());
    d.setAcceptMode(QFileDialog::AcceptOpen);
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
            _vendorPath->setText(files.first());
        }
    }
}

void SettingsEditor::onSaveClicked()
{
    Preferences::get()
            ->setVendorPath(_vendorPath->text())
            ->setJavaHeap(_javaHeap->value())
            ->setShowWhitespaces(_showWhitespaces->isChecked())
            ->setTabStopWidth(_tabStopWidth->value())
            ->setTextEncoding(_textEncoding->itemData(_textEncoding->currentIndex()).toInt())
            ->setUseSpacesForTabs(_useSpacesForTabs->isChecked())
            ->save();
    Dialog::accept();
}

APP_NAMESPACE_END
