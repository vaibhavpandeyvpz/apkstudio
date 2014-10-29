#include "toolbar.hpp"

namespace VPZ {
namespace APKStudio {
namespace Windows {

ToolBar::ToolBar(QWidget *parent) :
    QToolBar(parent)
{
    APKS_TOOLITEM(this, create, create, OpenApk);
    APKS_TOOLITEM(this, open, folder_open, OpenProject);
    addSeparator();
    APKS_TOOLITEM(this, save, disk, Save);
    APKS_TOOLITEM(this, save_all, disks, SaveAll);
    addSeparator();
    APKS_TOOLITEM(this, clean, broom, Clean);
    APKS_TOOLITEM(this, build, hammer, Build);
    addSeparator();
    APKS_TOOLITEM(this, terminal, terminal, Terminal);
    addSeparator();
    APKS_TOOLITEM(this, first, arrow_skip_left, First);
    APKS_TOOLITEM(this, previous, arrow_left, Previous);
    APKS_TOOLITEM(this, next, arrow_right, Next);
    APKS_TOOLITEM(this, last, arrow_skip_right, Last);
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(spacer);
    setAcceptDrops(false);
    setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    setObjectName("toolbar");
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ
