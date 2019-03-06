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
    bool sources() const;
private:
    QDialogButtonBox *m_ButtonBox;
    QCheckBox *m_CheckSources;
    QLineEdit *m_EditApk;
    QLineEdit *m_EditFolder;
    QWidget *buildButtonBox();
    QLayout *buildForm(const QString &apk);
private slots:
    void handleBrowseFolder();
    void handleButtonClick(QAbstractButton *button);
};

#endif // APKDECOMPILEDIALOG_H
