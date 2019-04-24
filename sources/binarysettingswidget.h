#ifndef BINARYSETTINGSWIDGET_H
#define BINARYSETTINGSWIDGET_H

#include <QLineEdit>
#include <QWidget>

class BinarySettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BinarySettingsWidget(QWidget *parent = nullptr);
private:
    QLineEdit *m_EditAdbExe;
    QLineEdit *m_EditApktoolJar;
    QLineEdit *m_EditJadxExe;
    QLineEdit *m_EditJavaExe;
    QLineEdit *m_EditUberApkSignerJar;
    QLayout *buildForm();
private slots:
    void handleBrowseAdb();
    void handleBrowseApktool();
    void handleBrowseJadx();
    void handleBrowseJava();
    void handleBrowseUberApkSigner();
public slots:
    void save();
};

#endif // BINARYSETTINGSWIDGET_H
