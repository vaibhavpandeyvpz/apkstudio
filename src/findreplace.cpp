#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include "include/findreplace.h"
#include "include/qrc.h"

APP_NAMESPACE_START

FindReplace::FindReplace(const bool r, QWidget *p)
    : Dialog(__(r ? "find_replace" : "find", "titles"), p), _replace(r)
{
    resize(QSize(360, 256));
    setMinimumSize(QSize(320, 192));
    setMaximumSize(QSize(480, 320));
    // Form : Start
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    QPushButton *find = new QPushButton(__("find", "buttons"), buttons);
    QPushButton *replace = new QPushButton(__("replace", "buttons"), buttons);
    QPushButton *replaceAll = new QPushButton(__("replace_all", "buttons"), buttons);
    QGroupBox *groupDirection = new QGroupBox(__("direction", "forms"), this);
    QGroupBox *groupFlags = new QGroupBox(__("flags", "forms"), this);
    _replaceWith = new QLineEdit(this);
    _searchFor = new QLineEdit(this);
    // Direction
    QRadioButton *directionUp = new QRadioButton(__("up", "forms"), this);
    // Layout
    QVBoxLayout *content = new QVBoxLayout;
    QVBoxLayout *directions = new QVBoxLayout;
    QVBoxLayout *flags = new QVBoxLayout;
    QFormLayout *form = new QFormLayout;
    QVBoxLayout *widget = new QVBoxLayout(this);
    QHBoxLayout *options = new QHBoxLayout;
    // Form : End
    buttons->addButton(find, QDialogButtonBox::AcceptRole);
    buttons->addButton(replace, QDialogButtonBox::ActionRole);
    buttons->addButton(replaceAll, QDialogButtonBox::ActionRole);
    directions->addWidget(directionUp);
    directions->addWidget(_directionDown = new QRadioButton(__("down", "forms"), this));
    flags->addWidget(_caseSensitive = new QCheckBox(__("case_sensitive", "forms"), this));
    flags->addWidget(_wholeText = new QCheckBox(__("whole_text", "forms"), this));
    flags->addWidget(_useRegex = new QCheckBox(__("use_regex", "forms"), this));
    form->addRow(__("search_for", "forms"), _searchFor);
    form->addRow(__("replace_with", "forms"), _replaceWith);
    content->addLayout(form);
    content->addLayout(options);
    groupDirection->setLayout(directions);
    groupFlags->setLayout(flags);
    options->addWidget(groupDirection);
    options->addWidget(groupFlags);
    widget->addLayout(content);
    widget->addWidget(buttons);
    setLayout(widget);
    _connections << connect(find, SIGNAL(clicked()), this, SLOT(onFindClick()));
    _connections << connect(replace, SIGNAL(clicked()), this, SLOT(onReplaceWithClick()));
    _connections << connect(replaceAll, SIGNAL(clicked()), this, SLOT(onReplaceAllWithClick()));
    _directionDown->setChecked(true);
    _searchFor->setFocus();
    if (!r)
    {
        replace->setEnabled(false);
        replaceAll->setEnabled(false);
        _replaceWith->setEnabled(false);
    }
}

void FindReplace::findInEditor(const bool n)
{
    if (_editor)
    {
        const QString &term = _searchFor->text();
        QTextDocument::FindFlags flags;
        if (!n)
        {
            flags |= QTextDocument::FindBackward;
        }
        if (_caseSensitive->isChecked())
        {
            flags |= QTextDocument::FindCaseSensitively;
        }
        if (_wholeText->isChecked())
        {
            flags |= QTextDocument::FindWholeWords;
        }
        bool r;
        QTextCursor cursor;
        if (_useRegex->isChecked())
        {
            QRegExp regex(term, (_caseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));
            cursor = _editor->document()->find(regex, cursor, flags);
            _editor->setTextCursor(cursor);
            r = !cursor.isNull();
        }
        else
        { r = _editor->find(term, flags); }
        if (!r)
        {
            cursor.setPosition(QTextCursor::Start);
            _editor->setTextCursor(cursor);
        }
    }
}

void FindReplace::onFindClick()
{
    findInEditor(_directionDown->isChecked());
}

void FindReplace::onReplaceWithClick()
{
    if (_editor && !_editor->isReadOnly())
    {
        if (!_editor->textCursor().hasSelection())
        {
            findInEditor(_directionDown->isChecked());
        }
        else
        {
            _editor->textCursor().insertText(_replaceWith->text());
            findInEditor(_directionDown->isChecked());
        }
    }
}

void FindReplace::onReplaceAllWithClick()
{
    if (_editor && !_editor->isReadOnly())
    {
        // int r = 0;
        while (_editor->textCursor().hasSelection())
        {
            _editor->textCursor().insertText(_replaceWith->text());
            findInEditor(_directionDown->isChecked());
            // r++;
        }
    }
}

APP_NAMESPACE_END
