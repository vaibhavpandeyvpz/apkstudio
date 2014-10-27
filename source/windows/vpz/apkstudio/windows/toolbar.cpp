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
    QComboBox *encoding = new QComboBox(this);
    encoding->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    encoding->setStyleSheet(STYLESHEET_COMBOBOXES);
    addWidget(encoding);
    refreshEncodings(encoding);
    connect(encoding, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index) {
        if (index < 0)
            return;
        Helpers::Settings::characterEncoding(qvariant_cast<int>(encoding->itemData(index)));
    });
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(spacer);
    setAcceptDrops(false);
    setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    setObjectName("toolbar");
}

void ToolBar::refreshEncodings(QComboBox *combo)
{
    combo->blockSignals(true);
    QList<int> mibs = QTextCodec::availableMibs();
    foreach (const int mib, mibs) {
        QTextCodec *codec = QTextCodec::codecForMib(mib);
        combo->addItem(codec->name(), QVariant(codec->mibEnum()));
    }
    combo->model()->sort(0);
    int index = combo->findData(QVariant(Helpers::Settings::characterEncoding()));
    if (index != -1)
       combo->setCurrentIndex(index);
    combo->blockSignals(false);
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ
