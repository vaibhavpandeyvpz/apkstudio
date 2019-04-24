#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPointer>
#include <QRadioButton>

class FindReplaceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FindReplaceDialog(const bool replace = false, QWidget *parent = nullptr);
    void setTextEdit(QPlainTextEdit *edit);
private:
    QDialogButtonBox *m_Buttons;
    QCheckBox *m_CheckCase;
    QCheckBox *m_CheckRegexp;
    QCheckBox *m_CheckWhole;
    QPointer<QPlainTextEdit> m_Edit;
    QLineEdit *m_EditFind;
    QLineEdit *m_EditReplacement;
    QRadioButton *m_RadioDown;
    QLabel *m_LabelMessage;
    QWidget *buildButtonBox(const bool replace);
    QLayout *buildForm(const bool replace);
    void findInTextEdit(const bool next);
private slots:
    void handleFind();
    void handleReplace();
    void handleReplaceAll();
};

#endif // FINDREPLACEDIALOG_H
