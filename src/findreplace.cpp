#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include "findreplace.h"
#include "qrc.h"

APP_NAMESPACE_START

FindReplace::FindReplace(const bool r, QWidget *p)
    : Dialog(Qrc::text(r ? "dialog.replace.title" : "dialog.find.title"), p), _editor(nullptr), _replace(r)
{
    resize(QSize(360, 256));
    setMinimumSize(QSize(320, 192));
    setMaximumSize(QSize(480, 320));
    // Form : Start
    auto buttons = new QDialogButtonBox(this);
    auto find = new QPushButton(Qrc::text("dialog.find.buttons.find"), buttons);
    auto replace = new QPushButton(Qrc::text("dialog.find.buttons.replace"), buttons);
    auto replaceAll = new QPushButton(Qrc::text("dialog.find.buttons.replace_all"), buttons);
    auto groupDirection = new QGroupBox(Qrc::text("dialog.find.group.direction"), this);
    auto groupFlags = new QGroupBox(Qrc::text("dialog.find.group.flags"), this);
    _replaceWith = new QLineEdit(this);
    _searchFor = new QLineEdit(this);
    // Direction
    auto directionUp = new QRadioButton(Qrc::text("dialog.find.radio.up"), this);
    // Layout
    auto content = new QVBoxLayout;
    auto directions = new QVBoxLayout;
    auto flags = new QVBoxLayout;
    auto form = new QFormLayout;
    auto widget = new QVBoxLayout(this);
    auto options = new QHBoxLayout;
    // Form : End
    buttons->addButton(find, QDialogButtonBox::AcceptRole);
    buttons->addButton(replace, QDialogButtonBox::ActionRole);
    buttons->addButton(replaceAll, QDialogButtonBox::ActionRole);
    directions->addWidget(directionUp);
    directions->addWidget(_directionDown = new QRadioButton(Qrc::text("dialog.find.radio.down"), this));
    flags->addWidget(_caseSensitive = new QCheckBox(Qrc::text("dialog.find.check.case_sensitive"), this));
    flags->addWidget(_wholeText = new QCheckBox(Qrc::text("dialog.find.check.whole_text"), this));
    flags->addWidget(_useRegex = new QCheckBox(Qrc::text("dialog.find.check.use_regex"), this));
    form->addRow(Qrc::text("dialog.find.form.search_for"), _searchFor);
    form->addRow(Qrc::text("dialog.find.form.replace_with"), _replaceWith);
    content->addLayout(form);
    content->addLayout(options);
    groupDirection->setLayout(directions);
    groupFlags->setLayout(flags);
    options->addWidget(groupDirection);
    options->addWidget(groupFlags);
    widget->addLayout(content);
    widget->addWidget(buttons);
    setLayout(widget);
    _connections << connect(find, &QPushButton::clicked, [=]
    {
        findInEditor(_directionDown->isChecked());
    });
    _connections << connect(replace, &QPushButton::clicked, this, &FindReplace::replaceWith);
    _connections << connect(replaceAll, &QPushButton::clicked, this, &FindReplace::replaceAllWith);
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
        const QString &searchFor = _searchFor->text();
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
        if (_useRegex->isChecked())
        {
            r = _editor->find(QRegExp(searchFor, (_caseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive)), flags);
        }
        else
        {
            r = _editor->find(searchFor, flags);
        }
        if (!r)
        {
            QTextCursor c = _editor->textCursor();
            c.setPosition(QTextCursor::Start);
            _editor->setTextCursor(c);
        }
    }
}

void FindReplace::replaceWith()
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

void FindReplace::replaceAllWith()
{
    if (_editor && !_editor->isReadOnly())
    {
        int r = 0;
        while (_editor->textCursor().hasSelection())
        {
            _editor->textCursor().insertText(_replaceWith->text());
            findInEditor(_directionDown->isChecked());
            r++;
        }
    }
}

APP_NAMESPACE_END
