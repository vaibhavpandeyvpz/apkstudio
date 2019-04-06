#include <QFormLayout>
#include <QGroupBox>
#include <QIcon>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "findreplacedialog.h"

FindReplaceDialog::FindReplaceDialog(const bool replace, QWidget *parent)
    : QDialog(parent), m_Edit(nullptr)
{
    auto layout = new QVBoxLayout(this);
    layout->addLayout(buildForm(replace));
    layout->addWidget(buildButtonBox(replace));
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(2);
    setMinimumSize(QSize(320, 192));
    setMaximumSize(QSize(480, 320));
#ifdef Q_OS_WIN
    setWindowIcon(QIcon(replace ? ":/icons/fugue/edit-replace.png" : ":/icons/fugue/binocular.png"));
#endif
    setWindowTitle(tr(replace ? "Find & Replace" : "Find"));
    m_EditFind->setFocus();
    m_RadioDown->setChecked(true);
}

QWidget *FindReplaceDialog::buildButtonBox(const bool replace)
{
    m_Buttons = new QDialogButtonBox(this);
    auto find = m_Buttons->addButton(tr("Find"), QDialogButtonBox::AcceptRole);
    connect(find, &QPushButton::clicked, this, &FindReplaceDialog::handleFind);
    if (replace) {
        auto replaceb = m_Buttons->addButton(tr("Replace"), QDialogButtonBox::ActionRole);
        auto replaceall = m_Buttons->addButton(tr("Replace All"), QDialogButtonBox::ActionRole);
        connect(replaceb, &QPushButton::clicked, this, &FindReplaceDialog::handleReplace);
        connect(replaceall, &QPushButton::clicked, this, &FindReplaceDialog::handleReplaceAll);
    }
    return m_Buttons;
}

QLayout *FindReplaceDialog::buildForm(const bool replace)
{
    auto directions = new QGroupBox(tr("Direction"), this);
    auto flags = new QGroupBox(tr("Flags"), this);
    auto directionsl = new QVBoxLayout(directions);
    auto flagsl = new QVBoxLayout(flags);
    auto form = new QFormLayout;
    directionsl->addWidget(new QRadioButton(tr("Up"), this));
    directionsl->addWidget(m_RadioDown = new QRadioButton(tr("Down"), this));
    flagsl->addWidget(m_CheckCase = new QCheckBox(tr("Case Sensitive"), this));
    flagsl->addWidget(m_CheckWhole = new QCheckBox(tr("Whole Text"), this));
    flagsl->addWidget(m_CheckRegexp = new QCheckBox(tr("Use Regexp"), this));
    form->addRow(tr("Find"), m_EditFind = new QLineEdit(this));
    if (replace) {
        form->addRow(tr("Replace"), m_EditReplacement = new QLineEdit(this));
    }
    auto options = new QHBoxLayout;
    options->addWidget(directions);
    options->addWidget(flags);
    auto layout = new QVBoxLayout;
    layout->addLayout(form);
    layout->addLayout(options);
    layout->addWidget(m_LabelMessage = new QLabel(tr("Ready!"), this));
    m_LabelMessage->setAlignment(Qt::AlignTop | Qt::AlignRight);
    m_LabelMessage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return layout;
}

void FindReplaceDialog::findInTextEdit(const bool next)
{
    bool found = false;
    if (m_Edit) {
        m_LabelMessage->setText(QString());
        const QString term = m_EditFind->text();
        QTextDocument::FindFlags flags;
        if (!next) {
            flags |= QTextDocument::FindBackward;
        }
        if (m_CheckCase->isChecked()) {
            flags |= QTextDocument::FindCaseSensitively;
        }
        if (m_CheckWhole->isChecked()) {
            flags |= QTextDocument::FindWholeWords;
        }
        QTextCursor cursor;
        if (m_CheckRegexp->isChecked()) {
            QRegExp regex(term, (m_CheckCase->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));
            cursor = m_Edit->document()->find(regex, cursor, flags);
            m_Edit->setTextCursor(cursor);
            found = !cursor.isNull();
        } else {
            found = m_Edit->find(term, flags);
        }
        if (!found) {
            cursor.setPosition(QTextCursor::Start);
            m_Edit->setTextCursor(cursor);
        }
    }
    if (!found) {
        m_LabelMessage->setText(tr("Could not find the search term."));
    }
}

void FindReplaceDialog::handleFind()
{
    findInTextEdit(m_RadioDown->isChecked());
}

void FindReplaceDialog::handleReplace()
{
    if (m_Edit && !m_Edit->isReadOnly()) {
        if (m_Edit->textCursor().hasSelection()) {
            m_Edit->textCursor().insertText(m_EditReplacement->text());
            findInTextEdit(m_RadioDown->isChecked());
        } else {
            findInTextEdit(m_RadioDown->isChecked());
        }
    }
}

void FindReplaceDialog::handleReplaceAll()
{
    if (m_Edit && !m_Edit->isReadOnly()) {
        int i = 0;
        while (m_Edit->textCursor().hasSelection()) {
            m_Edit->textCursor().insertText(m_EditReplacement->text());
            findInTextEdit(m_RadioDown->isChecked());
            i++;
        }
        m_LabelMessage->setText(tr("Replace %1 occurrences of the search term.").arg(i));
    }
}

void FindReplaceDialog::setTextEdit(QPlainTextEdit *edit)
{
    m_Edit = edit;
}
