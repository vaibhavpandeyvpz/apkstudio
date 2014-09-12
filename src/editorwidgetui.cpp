#include "editorwidgetui.h"

void EditorWidgetUI::prepare()
{
    // Initialize: Layout
    _hlayout = new QHBoxLayout();
    _hlayout->setContentsMargins(QMargins(0, 0, 0, 0));
    _hlayout->setSpacing(0);
    _vlayout = new QVBoxLayout(this);
    _vlayout->setContentsMargins(QMargins(0, 0, 0, 0));
    _vlayout->setSpacing(0);
    // Initialize: ToolBars
    _toolbar_left = new QToolBar(this);
    _toolbar_left->setAcceptDrops(false);
    _toolbar_left->setMovable(false);
    _toolbar_top = new QToolBar(this);
    _toolbar_top->setAcceptDrops(false);
    _toolbar_top->setMovable(false);
    // Initialize: Actions
    _close = new QAction(icon("cross"), translate("item_close"), _toolbar_top);
    _split_horizontal = new QAction(icon("split_horizontal"), translate("item_split_horizontal"), _toolbar_top);
    _split_vertical = new QAction(icon("split_vertical"), translate("item_split_vertical"), _toolbar_top);
    // Initialize: Labels
    _detail = new QLabel(_toolbar_top);
    // Initialize: ComboBoxes
    _primary = new QComboBox(_toolbar_top);
    _primary->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _primary->setStyleSheet(STYLESHEET_COMBOBOXES);
    _secondary = new QComboBox(_toolbar_top);
    _secondary->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _secondary->setStyleSheet(STYLESHEET_COMBOBOXES);
    // Add: ComboBoxes
    _toolbar_top->addWidget(_primary);
    _toolbar_top->addWidget(_secondary);
    // Add: Labels
    _toolbar_top->addWidget(_detail);
    // Add: Actions
    _toolbar_top->addAction(_split_horizontal);
    _toolbar_top->addAction(_split_vertical);
    _toolbar_top->addSeparator();
    _toolbar_top->addAction(_close);
    // Add: Toolbar
    _hlayout->addWidget(_toolbar_left);
    _vlayout->addWidget(_toolbar_top);
    _vlayout->addLayout(_hlayout);
    // Add: Layout
    _vlayout->addLayout(_hlayout);
    setLayout(_vlayout);
}
