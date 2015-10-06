#ifndef SETTINGSEDITOR_H
#define SETTINGSEDITOR_H

#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include "dialog.h"

AS_NAMESPACE_START

class SettingsEditor : public Dialog
{
    Q_OBJECT
private:
    QLineEdit *_binariesPath;
    QSpinBox *_javaHeap;
    QCheckBox *_showWhitespaces;
    QSpinBox *_tabStopWidth;
    QCheckBox *_useSpacesForTabs;
private slots:
    void onSaveClicked();
public:
    explicit SettingsEditor(QWidget *parent = 0);
};

AS_NAMESPACE_END

#endif // SETTINGSEDITOR_H
