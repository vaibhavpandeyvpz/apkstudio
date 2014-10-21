#include "bracketmatcher.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

BracketMatcher::BracketMatcher(QPlainTextEdit *editor, const QString &color)
    : color(QColor(color))
{
    this->editor = editor;
}

void BracketMatcher::highlight(const int position)
{
    QTextCharFormat format;
    format.setBackground(color);
    QTextEdit::ExtraSelection selection;
    selection.cursor = editor->textCursor();
    selection.cursor.setPosition(position);
    selection.cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    selection.format = format;
    QList<QTextEdit::ExtraSelection> selections = editor->extraSelections();
    selections.append(selection);
    editor->setExtraSelections(selections);
}

bool BracketMatcher::left(const QChar left, const QChar right, QTextBlock block, int start, int skip)
{
    Block *data = static_cast<Block *>(block.userData());
    QVector<Resources::Bracket *> brackets;
    int position;
    if (!data)
        goto loop;
    brackets = data->brackets;
    position = block.position();
    for (; start < brackets.size(); ++start) {
        Resources::Bracket *bracket = brackets.at(start);
        if (bracket->character == left) {
            ++skip;
            continue;
        } else if ((bracket->character == right) && (skip == 0)) {
            highlight(position + bracket->position);
            return true;
        } else
            --skip;
    }
    loop:
    block = block.next();
    if (block.isValid())
        return this->left(left, right, block, 0, skip);
    return false;
}

void BracketMatcher::match(const QChar left, const QChar right)
{
    Block *data = static_cast<Block *>(editor->textCursor().block().userData());
    if (!data)
        return;
    QVector<Resources::Bracket *> brackets = data->brackets;
    int position = editor->textCursor().block().position();
    for (int index = 0; index < brackets.size(); ++index) {
        Resources::Bracket *bracket = brackets.at(index);
        int current = editor->textCursor().position() - editor->textCursor().block().position();
        if ((bracket->position == (current - 1)) && (bracket->character == left)) {
            if (this->left(left, right, editor->textCursor().block(), index + 1, 0))
                highlight(position + bracket->position);
        } else if ((bracket->position == (current - 1)) && (bracket->character == right)) {
            if (this->right(left, right, editor->textCursor().block(), index - 1, 0, true))
                highlight(position + bracket->position);
        }
    }
}

bool BracketMatcher::right(const QChar left, const QChar right, QTextBlock block, int start, int skip, bool first)
{
    Block *data = static_cast<Block *>(block.userData());
    QVector<Resources::Bracket *> brackets;
    int position;
    if (!data)
        goto loop;
    brackets = data->brackets;
    if (!first)
        start = (brackets.size() - 1);
    position = block.position();
    for (; (start > -1) && (brackets.size() > 0); --start) {
        Resources::Bracket *bracket = brackets.at(start);
        if (bracket->character == right) {
            ++skip;
            continue;
        } else if ((bracket->character == left) && (skip == 0)) {
            highlight(position + bracket->position);
            return true;
        } else
            --skip;
    }
    loop:
    block = block.previous();
    if (block.isValid())
        return this->right(left, right, block, 0, skip);
    return false;
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
