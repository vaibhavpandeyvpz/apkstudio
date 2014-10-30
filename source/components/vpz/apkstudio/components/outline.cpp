#include "outline.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Outline::Outline(QWidget *parent) :
    Dockable(translate("title_dock"), parent)
{
    tree = new QTreeWidget(this);
    tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tree->setMinimumSize(64, 64);
    tree->setSelectionBehavior(QAbstractItemView::SelectItems);
    tree->setSelectionMode(QAbstractItemView::SingleSelection);
    tree->setSortingEnabled(false);
    tree->setUniformRowHeights(true);
    QStringList labels;
    labels << translate("header_symbol");
    labels << translate("header_type");
    tree->setHeaderLabels(labels);
    setObjectName("outline");
    setWidget(tree);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
