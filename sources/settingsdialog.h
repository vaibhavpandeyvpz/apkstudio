#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QStackedWidget>
#include <QWidget>
#include "appearancesettingswidget.h"
#include "binarysettingswidget.h"
#include "signingconfigwidget.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(const int page = 0, QWidget *parent = nullptr);
private:
    AppearanceSettingsWidget *m_AppearanceSettingsWidget;
    BinarySettingsWidget *m_BinarySettingsWidget;
    SigningConfigWidget *m_SigningConfigWidget;
    QDialogButtonBox *m_ButtonBox;
    QListWidget *m_OptionsList;
    QStackedWidget *m_WidgetStack;
    QWidget *buildButtonBox();
    QLayout *buildForm();
};

#endif // SETTINGSDIALOG_H
