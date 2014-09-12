#include "toolbarui.h"

void ToolBarUI::onEncodingSelected(int index)
{
    if (index < 0)
        return;
    Settings::characterEncoding(qvariant_cast<int>(_encoding->itemData(index)));
}

void ToolBarUI::prepare()
{
    // Initialize: Actions
    _build = new QAction(icon("hammer"), translate("item_build"), this);
    _clean = new QAction(icon("broom"), translate("item_clean"), this);
    _first = new QAction(icon("arrow_skip_left"), translate("item_first"), this);
    _full_screen = new QAction(icon("arrow_in_out"), translate("item_full_screen"), this);
    _last = new QAction(icon("arrow_skip_right"), translate("item_last"), this);
    _new = new QAction(icon("new"), translate("item_new"), this);
    _next = new QAction(icon("arrow_right"), translate("item_next"), this);
    _open = new QAction(icon("folder_open"), translate("item_open"), this);
    _previous = new QAction(icon("arrow_left"), translate("item_previous"), this);
    _save = new QAction(icon("disk"), translate("item_save"), this);
    _save_all = new QAction(icon("disks"), translate("item_save_all"), this);
    _terminal = new QAction(icon("terminal"), translate("item_terminal"), this);
    _windowed = new QAction(icon("arrow_in"), translate("item_windowed"), this);
    // Initialize: ComboBoxes
    _encoding = new QComboBox(this);
    _encoding->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    _encoding->setStyleSheet(STYLESHEET_COMBOBOXES);
    // Initialize: Self
    setAcceptDrops(false);
    setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    // Add: Actions
    addAction(_new);
    addAction(_open);
    addSeparator();
    addAction(_save);
    addAction(_save_all);
    addSeparator();
    addAction(_clean);
    addAction(_build);
    addSeparator();
    addAction(_terminal);
    addSeparator();
    addAction(_first);
    addAction(_previous);
    addAction(_next);
    addAction(_last);
    addWidget(_encoding);
    // Add: Spacer
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(spacer);
    // Bind: ComboBoxes
    connect(_encoding, SIGNAL(currentIndexChanged(int)), this, SLOT(onEncodingSelected(int)));
}
