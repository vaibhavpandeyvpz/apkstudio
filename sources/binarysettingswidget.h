#ifndef BINARYSETTINGSWIDGET_H
#define BINARYSETTINGSWIDGET_H

#include <QLineEdit>
#include <QWidget>

class BinarySettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BinarySettingsWidget(const QString &focus, QWidget *parent = nullptr);
    QString apktoolJar() const;
    QString jadxExe() const;
    QString javaExe() const;
    QLayout *buildForm();
private:
    QLineEdit *m_EditApktoolJar;
    QLineEdit *m_EditJadxExe;
    QLineEdit *m_EditJavaExe;
private slots:
    void handleBrowseApktool();
    void handleBrowseJadx();
    void handleBrowseJava();
};

#endif // BINARYSETTINGSWIDGET_H
