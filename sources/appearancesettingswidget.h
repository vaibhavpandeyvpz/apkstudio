#ifndef APPERANCESETTINGSWIDGET_H
#define APPERANCESETTINGSWIDGET_H

#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QWidget>

class AppearanceSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AppearanceSettingsWidget(QWidget *parent = nullptr);
private:
    QCheckBox *m_CheckShowWhitespaces;
    QComboBox *m_ComboEditorFont;
    QRadioButton *m_RadioThemeDark;
    QSpinBox *m_SpinEditorFontSize;
    QLayout *buildForm();
public slots:
    void save();
};

#endif // APPERANCESETTINGSWIDGET_H
