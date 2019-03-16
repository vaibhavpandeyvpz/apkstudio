#ifndef SOURCECODEEDIT_H
#define SOURCECODEEDIT_H

#include <QPlainTextEdit>

class SourceCodeEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit SourceCodeEdit(QWidget *parent = nullptr);
};

#endif // SOURCECODEEDIT_H
