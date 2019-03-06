#ifndef BINARYSETTINGSWIDGET_H
#define BINARYSETTINGSWIDGET_H

#include <QLineEdit>
#include <QWidget>

class BinarySettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BinarySettingsWidget(const QString &focus, QWidget *parent = nullptr);
    QString adbExe() const;
    QString apktoolJar() const;
    QString jadxExe() const;
    QString javaExe() const;
    QString uberApkSignerJar() const;
    QLayout *buildForm();
private:
    QLineEdit *m_EditAdbExe;
    QLineEdit *m_EditApktoolJar;
    QLineEdit *m_EditJadxExe;
    QLineEdit *m_EditJavaExe;
    QLineEdit *m_EditUberApkSignerJar;
private slots:
    void handleBrowseAdb();
    void handleBrowseApktool();
    void handleBrowseJadx();
    void handleBrowseJava();
    void handleBrowseUberApkSigner();
};

#endif // BINARYSETTINGSWIDGET_H
