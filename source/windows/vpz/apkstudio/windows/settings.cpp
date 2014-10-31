#include "settings.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

Settings::Settings(QWidget *parent) :
    Dialog(parent)
{
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    QHBoxLayout *hlayout = new QHBoxLayout(this);
    QSizePolicy left(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy right(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QWidget *temp = new QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(temp);
    stack = new QStackedWidget(this);
    list = new QListWidget(this);
    buttons->addButton(translate("button_cancel"), QDialogButtonBox::RejectRole);
    buttons->addButton(translate("button_save"), QDialogButtonBox::AcceptRole);
    hlayout->addWidget(list);
    hlayout->addWidget(temp);
    hlayout->setContentsMargins(2, 2, 2, 2);
    hlayout->setSpacing(2);
    left.setHorizontalStretch(1);
    list->setContextMenuPolicy(Qt::CustomContextMenu);
    list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    list->setSelectionBehavior(QAbstractItemView::SelectItems);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    list->setSizePolicy(left);
    list->setSortingEnabled(false);
    right.setHorizontalStretch(2);
    temp->setLayout(vlayout);
    temp->setSizePolicy(right);
    vlayout->addWidget(stack);
    vlayout->addWidget(buttons);
    vlayout->setContentsMargins(QMargins(2, 2, 2, 2));
    vlayout->setSpacing(0);
    connections.append(connect(buttons, SIGNAL(accepted()), this, SLOT(accept())));
    connections.append(connect(buttons, SIGNAL(rejected()), this, SLOT(reject())));
    connections.append(connect(list->selectionModel(), &QItemSelectionModel::selectionChanged, [ this ] (QItemSelection, QItemSelection) {
        QModelIndexList selection = this->list->selectionModel()->selectedRows(0);
        if (selection.count() != 1)
            return;
        this->stack->setCurrentIndex(selection.first().row());
    }));
    createGeneralTab();
    createEditorTab();
    createViewerTab();
    createJavaTab();
    createADBTab();
    createApktoolTab();
    setLayout(hlayout);
    setWindowTitle(translate("title_window"));
}

void Settings::createADBTab()
{
    QWidget *widget = new QWidget(stack);
    QFormLayout *layout = new QFormLayout(widget);
    QCheckBox *root = new QCheckBox(widget);
    layout->addRow(translate("label_root"), root);
    root->setChecked(Helpers::Settings::rootShell());
    widget->setLayout(layout);
    connections.append(connect(this, &QDialog::accepted, [ root ] () {
        Helpers::Settings::rootShell(root->isChecked());
    }));
    list->addItem(translate("item_adb"));
    stack->addWidget(widget);
}

void Settings::createApktoolTab()
{
    QWidget *widget = new QWidget(stack);
    QFormLayout *layout = new QFormLayout(widget);
    QLineEdit *certificate = new QLineEdit(widget);
    QLineEdit *framework = new QLineEdit(widget);
    QLineEdit *key = new QLineEdit(widget);
    QPushButton *cbrowse = new QPushButton(translate("button_browse"), widget);
    QPushButton *fbrowse = new QPushButton(translate("button_browse"), widget);
    QPushButton *kbrowse = new QPushButton(translate("button_browse"), widget);
    certificate->setText(Helpers::Settings::signingCertificate());
    framework->setText(Helpers::Settings::frameworkPath());
    key->setText(Helpers::Settings::signingKey());
    layout->addRow(translate("label_framework"), framework);
    layout->addRow("", fbrowse);
    layout->addRow(translate("label_certificate"), certificate);
    layout->addRow("", cbrowse);
    layout->addRow(translate("label_key"), key);
    layout->addRow("", kbrowse);
    widget->setLayout(layout);
    connections.append(connect(cbrowse, &QPushButton::clicked, [ certificate, this ] () {
        QFileDialog dialog(this, translate("title_select"), Helpers::Settings::previousDirectory(), "x509 Certificate (*.pem)");
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setFileMode(QFileDialog::ExistingFile);
        if (dialog.exec() != QFileDialog::Accepted)
            return;
        QStringList files = dialog.selectedFiles();
        if (files.isEmpty())
            return;
        Helpers::Settings::previousDirectory(dialog.directory().absolutePath());
        certificate->setText(files.first());
    }));
    connections.append(connect(fbrowse, &QPushButton::clicked, [ framework, this ] () {
        QString path = QFileDialog::getExistingDirectory(this, translate("title_choose_directory"), Helpers::Settings::previousDirectory());
        if (path.isEmpty())
            return;
        Helpers::Settings::previousDirectory(path);
        framework->setText(path);
    }));
    connections.append(connect(kbrowse, &QPushButton::clicked, [ key, this ] () {
        QFileDialog dialog(this, translate("title_select"), Helpers::Settings::previousDirectory(), "Private Key (*.pk8)");
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setFileMode(QFileDialog::ExistingFile);
        if (dialog.exec() != QFileDialog::Accepted)
            return;
        QStringList files = dialog.selectedFiles();
        if (files.isEmpty())
            return;
        Helpers::Settings::previousDirectory(dialog.directory().absolutePath());
        key->setText(files.first());
    }));
    connections.append(connect(this, &QDialog::accepted, [ certificate, framework, key ] () {
        Helpers::Settings::frameworkPath(framework->text());
        Helpers::Settings::signingCertificate(certificate->text());
        Helpers::Settings::signingKey(key->text());
    }));
    widget->setLayout(layout);
    list->addItem(translate("item_apktool"));
    stack->addWidget(widget);
    fixButtonSize(cbrowse);
    fixButtonSize(fbrowse);
    fixButtonSize(kbrowse);
}

void Settings::createEditorTab()
{
    QWidget *widget = new QWidget(stack);
    QFormLayout *layout = new QFormLayout(widget);
    QSpinBox *cursor = new QSpinBox(widget);
    QComboBox *encoding = new QComboBox(widget);
    QComboBox *font = new QComboBox(widget);
    QStringList fonts = QFontDatabase().families();
    QList<int> mibs = QTextCodec::availableMibs();
    QComboBox *size = new QComboBox(widget);
    QCheckBox *spaces = new QCheckBox(widget);
    QSpinBox *tab = new QSpinBox(widget);
    QCheckBox *whitespace = new QCheckBox(widget);
    QCheckBox *wrap = new QCheckBox(widget);
    cursor->setRange(1, 96);
    cursor->setSingleStep(1);
    cursor->setSuffix(" px");
    cursor->setValue(Helpers::Settings::cursorWidth());
    foreach (const int mib, mibs) {
        QTextCodec *codec = QTextCodec::codecForMib(mib);
        encoding->addItem(codec->name(), codec->mibEnum());
    }
    encoding->setCurrentIndex(encoding->findData(Helpers::Settings::characterEncoding()));
    foreach (const QString &family, fonts)
        font->addItem(family, family);
    font->setCurrentIndex(font->findData(Helpers::Settings::fontFamily()));
    for (int i = 8; i <= 72; (i += 3)) {
        size->addItem(QString::number(i), QString::number(i));
        if (i != 8)
            continue;
        size->addItem(QString::number(10), QString::number(10));
    }
    size->setCurrentIndex(size->findData(Helpers::Settings::fontSize()));
    spaces->setChecked(Helpers::Settings::spacesForTab());
    tab->setRange(1, 8);
    tab->setSingleStep(1);
    tab->setValue(Helpers::Settings::tabWidth());
    whitespace->setChecked(Helpers::Settings::showWhitespace());
    wrap->setChecked(Helpers::Settings::wordWrap());
    layout->addRow(translate("label_encoding"), encoding);
    layout->addRow(translate("label_cursor"), cursor);
    layout->addRow(translate("label_font"), font);
    layout->addRow(translate("label_size"), size);
    layout->addRow(translate("label_spaces"), spaces);
    layout->addRow(translate("label_tab"), tab);
    layout->addRow(translate("label_whitespace"), whitespace);
    layout->addRow(translate("label_wrap"), wrap);
    widget->setLayout(layout);
    connections.append(connect(this, &QDialog::accepted, [ cursor, encoding, font, size, spaces, tab, whitespace, wrap ] () {
        Helpers::Settings::characterEncoding(encoding->itemData(encoding->currentIndex()).value<int>());
        Helpers::Settings::cursorWidth(cursor->value());
        Helpers::Settings::fontFamily(font->itemData(font->currentIndex()).value<QString>());
        Helpers::Settings::fontSize(size->itemData(size->currentIndex()).value<int>());
        Helpers::Settings::showWhitespace(whitespace->isChecked());
        Helpers::Settings::spacesForTab(spaces->isChecked());
        Helpers::Settings::tabWidth(tab->value());
        Helpers::Settings::wordWrap(wrap->isChecked());
    }));
    list->addItem(translate("item_editor"));
    stack->addWidget(widget);
}

void Settings::createGeneralTab()
{
    QWidget *widget = new QWidget(stack);
    QFormLayout *layout = new QFormLayout(widget);
    layout->setContentsMargins(4, 4, 4, 4);
    QLineEdit *binary = new QLineEdit(widget);
    QPushButton *browse = new QPushButton(translate("button_browse"), widget);
    QComboBox *language = new QComboBox(widget);
    QComboBox *theme = new QComboBox(widget);
    binary->setText(Helpers::Settings::binaryPath());
    language->addItem(translate("language_english"), "en");
    language->setCurrentIndex(language->findData(Helpers::Settings::language()));
    layout->addRow(translate("label_theme"), theme);
    layout->addRow(translate("label_language"), language);
    layout->addRow(translate("label_binary"), binary);
    layout->addRow("", browse);
    theme->addItem(translate("theme_default"), "default");
    theme->addItem(translate("theme_light"), "light");
    theme->addItem(translate("theme_dark"), "dark");
    theme->setCurrentIndex(theme->findData(Helpers::Settings::theme()));
    widget->setLayout(layout);
    connections.append(connect(browse, &QPushButton::clicked, [ binary, this ] () {
        QString path = QFileDialog::getExistingDirectory(this, translate("title_choose_directory"), Helpers::Settings::previousDirectory());
        if (path.isEmpty())
            return;
        Helpers::Settings::previousDirectory(path);
        binary->setText(path);
    }));
    connections.append(connect(this, &QDialog::accepted, [ binary, language, theme ] () {
        Helpers::Settings::binaryPath(binary->text());
        Helpers::Settings::language(language->itemData(language->currentIndex()).value<QString>());
        Helpers::Settings::theme(theme->itemData(theme->currentIndex()).value<QString>());
    }));
    list->addItem(translate("item_general"));
    stack->addWidget(widget);
    fixButtonSize(browse);
}

void Settings::createJavaTab()
{
    QWidget *widget = new QWidget(stack);
    QFormLayout *layout = new QFormLayout(widget);
    QSpinBox *heap = new QSpinBox(widget);
    QLineEdit *java = new QLineEdit(widget);
    QPushButton *browse = new QPushButton(translate("button_browse"), widget);
    heap->setRange(8, 2048);
    heap->setSingleStep(1);
    heap->setSuffix(" MBs");
    heap->setValue(Helpers::Settings::heapSize());
    java->setText(Helpers::Settings::javaHome());
    layout->addRow(translate("label_java"), java);
    layout->addRow("", browse);
    layout->addRow(translate("label_heap"), heap);
    widget->setLayout(layout);
    connections.append(connect(browse, &QPushButton::clicked, [ java, this ] () {
        QString path = QFileDialog::getExistingDirectory(this, translate("title_choose_directory"), Helpers::Settings::previousDirectory());
        if (path.isEmpty())
            return;
        Helpers::Settings::previousDirectory(path);
        java->setText(path);
    }));
    connections.append(connect(this, &QDialog::accepted, [ heap, java ] () {
        Helpers::Settings::heapSize(heap->value());
        Helpers::Settings::javaHome(java->text());
    }));
    list->addItem(translate("item_java"));
    stack->addWidget(widget);
    fixButtonSize(browse);
}

void Settings::createViewerTab()
{
    QWidget *widget = new QWidget(stack);
    QFormLayout *layout = new QFormLayout(widget);
    QComboBox *background = new QComboBox(widget);
    background->addItem(translate("color_transparent"), "transparent");
    background->addItem(translate("color_white"), "#FFFFFF");
    background->addItem(translate("color_grey"), "#999999");
    background->setCurrentIndex(background->findData(Helpers::Settings::imageBackground()));
    layout->addRow(translate("label_background"), background);
    widget->setLayout(layout);
    connections.append(connect(this, &QDialog::accepted, [ background ] () {
        Helpers::Settings::imageBackground(background->itemData(background->currentIndex()).value<QString>());
    }));
    list->addItem(translate("item_viewer"));
    stack->addWidget(widget);
}

void Settings::fixButtonSize(QPushButton *button)
{
    QSize size = button->fontMetrics().size(Qt::TextShowMnemonic, button->text());
    size.setWidth(size.width() + 12);
    QStyleOptionButton option;
    option.initFrom(button);
    option.rect.setSize(size);
    button->setMaximumSize(button->style()->sizeFromContents(QStyle::CT_PushButton, &option, size, button));
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ
