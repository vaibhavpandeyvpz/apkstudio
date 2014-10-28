#include "editor.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

Editor::Editor(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QToolBar *tool_bar = new QToolBar(this);
    extra = new QComboBox(tool_bar);
    files = new QComboBox(tool_bar);
    stack = new QStackedWidget(this);
    symbols = new QComboBox(tool_bar);
    layout->addWidget(tool_bar);
    layout->addWidget(stack);
    layout->setContentsMargins(QMargins(0, 0, 0, 0));
    layout->setSpacing(0);
    symbols->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tool_bar->addWidget(files);
    tool_bar->addWidget(symbols);
    tool_bar->addWidget(extra);
    setLayout(layout);
    setMinimumSize(64, 64);
    stack->addWidget(new Coder(stack));
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
