#ifndef SETTINGSEDITOR_H
#define SETTINGSEDITOR_H

#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include "dialog.h"

APP_NAMESPACE_START

class SettingsEditor : public Dialog
{
    Q_OBJECT
private:
    QLineEdit *_vendorPath;
    QSpinBox *_javaHeap;
    QCheckBox *_showWhitespaces;
    QSpinBox *_tabStopWidth;
    QComboBox *_textEncoding;
    QCheckBox *_useSpacesForTabs;
private Q_SLOTS:
    void onBrowseVendor();
    void onSaveClicked();
public:
    explicit SettingsEditor(QWidget *parent = 0);
};

APP_NAMESPACE_END

#endif // SETTINGSEDITOR_H
