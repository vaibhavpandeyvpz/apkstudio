#include <QApplication>
#include <QFontComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSettings>
#include "appearancesettingswidget.h"

#define CODE_RESTART 60600

AppearanceSettingsWidget::AppearanceSettingsWidget(QWidget *parent)
    : QWidget(parent)
{
    setLayout(buildForm());
}

QLayout *AppearanceSettingsWidget::buildForm()
{
    auto layout = new QFormLayout();
    auto themes = new QHBoxLayout();
    QRadioButton *light = new QRadioButton(tr("Light"), this);
    themes->addWidget(light);
    themes->addWidget(m_RadioThemeDark = new QRadioButton(tr("Dark"), this));
    layout->addRow(tr("Theme"), themes);
    layout->addRow(tr("Editor Font"), m_ComboEditorFont = new QFontComboBox(this));
    layout->addRow(tr("Editor Font Size"), m_SpinEditorFontSize = new QSpinBox(this));
    m_SpinEditorFontSize->setMinimum(10);
    m_SpinEditorFontSize->setSingleStep(1);
    layout->addRow(tr("Show Whitespaces?"), m_CheckShowWhitespaces = new QCheckBox(this));
    QSettings settings;
    const bool dark = settings.value("dark_theme", false).toBool();
    if (dark) {
        m_RadioThemeDark->setChecked(true);
    } else {
        light->setChecked(true);
    }
#ifdef Q_OS_WIN
    const QString font = settings.value("editor_font", "Courier New").toString();
#elif defined(Q_OS_MACOS)
    const QString font = settings.value("editor_font", "Monaco").toString();
#else
    const QString font = settings.value("editor_font", "Ubuntu Mono").toString();
#endif
    m_ComboEditorFont->setCurrentText(font);
    m_SpinEditorFontSize->setValue(settings.value("editor_font_size", 10).toInt());
    m_CheckShowWhitespaces->setChecked(settings.value("editor_whitespaces", false).toBool());
    return layout;
}

void AppearanceSettingsWidget::save()
{
    QSettings settings;
    bool dark = settings.value("dark_theme").toBool();
    settings.setValue("dark_theme", m_RadioThemeDark->isChecked());
    settings.setValue("editor_font", m_ComboEditorFont->currentText());
    settings.setValue("editor_font_size", m_SpinEditorFontSize->value());
    settings.setValue("editor_whitespaces", m_CheckShowWhitespaces->isChecked());
    settings.sync();
    if (dark != m_RadioThemeDark->isChecked()) {
        int btn = QMessageBox::information(this,
                                           tr("Theme"),
                                           tr("Changes to app theme will be applied only when you restart APK studio."),
                                           tr("Restart"),
                                           tr("OK"));
        if (btn == 0) {
            QApplication::exit(CODE_RESTART);
        }
    }
}
