#ifndef APKDECOMPILEDIALOG_H
#define APKDECOMPILEDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>

class ApkDecompileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ApkDecompileDialog(const QString &apk, QWidget *parent = nullptr);
    QString apk() const;
    QString folder() const;
    bool java() const;
    bool resources() const;
    bool smali() const;
    QString frameworkTag() const;
    QString extraArguments() const;
private:
    QDialogButtonBox *m_ButtonBox;
    QCheckBox *m_CheckJava;
    QCheckBox *m_CheckResources;
    QCheckBox *m_CheckSmali;
    QLineEdit *m_EditApk;
    QLineEdit *m_EditFolder;
    QLineEdit *m_EditFrameworkTag;
    QLineEdit *m_EditExtraArguments;
    QWidget *buildButtonBox();
    QLayout *buildForm(const QString &apk);
private slots:
    void handleBrowseFolder();
};

#endif // APKDECOMPILEDIALOG_H
