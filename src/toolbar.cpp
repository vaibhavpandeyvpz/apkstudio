#include "toolbar.h"

void ToolBar::invalidate()
{
    // Populate: ComboBoxes
    _encoding->blockSignals(true);
    QList<int> mibs = QTextCodec::availableMibs();
    foreach (const int &mib, mibs) {
        QTextCodec *codec = QTextCodec::codecForMib(mib);
        _encoding->addItem(codec->name(), QVariant(codec->mibEnum()));
    }
    _encoding->model()->sort(0);
    int index = _encoding->findData(QVariant(Settings::defaultEncoding()));
    if (index != -1)
       _encoding->setCurrentIndex(index);
    _encoding->blockSignals(false);
}
