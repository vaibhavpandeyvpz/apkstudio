#ifndef FINDREPLACE_H
#define FINDREPLACE_H

#include <QCheckBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPointer>
#include <QRadioButton>
#include "dialog.h"
#include "macros.h"

AS_NAMESPACE_START

class FindReplace : public Dialog
{
    Q_OBJECT
private:
    QPointer<QPlainTextEdit> _editor;
    QCheckBox *_caseSensitive;
    QRadioButton *_directionDown;
    bool _replace;
    QLineEdit *_replaceWith;
    QLineEdit *_searchFor;
    QCheckBox *_useRegex;
    QCheckBox *_wholeText;
private:
    void findInEditor(const bool next);
private slots:
    void replaceWith();
    void replaceAllWith();
public:
    explicit FindReplace(const bool replaceWith, QWidget *parent = 0);
    inline void setEditor(QPlainTextEdit *editor) { _editor = editor; }
};

AS_NAMESPACE_END

#endif // FINDREPLACE_H
