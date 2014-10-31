#include "bracketmatcher.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

BracketMatcher::BracketMatcher(QPlainTextEdit *editor)
    : editor(editor)
{
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

bool BracketMatcher::left(const QChar left, const QChar right, QTextBlock block, int start, int skip, bool first)
{
    Block *data = static_cast<Block *>(block.userData());
    QList<Resources::Bracket *> brackets;
    int position;
    if (!data)
        goto loop;
    brackets = data->brackets;
    if (!first)
        start = 0;
    position = block.position();
    for (; start < brackets.size(); ++start) {
        Resources::Bracket *bracket = brackets.at(start);
        if (bracket->character == left) {
            ++skip;
            continue;
        } else if (bracket->character == right) {
            if (skip == 0) {
                highlight(position + bracket->position);
                return true;
            } else
                --skip;
        }
    }
    loop:
    block = block.next();
    return block.isValid() ? this->left(left, right, block, 0, skip) : false;
}

void BracketMatcher::match(const QChar left, const QChar right)
{
    QTextCursor cursor = editor->textCursor();
    QTextBlock block = cursor.block();
    Block *data = static_cast<Block *>(block.userData());
    if (!data)
        return;
    QList<Resources::Bracket *> brackets = data->brackets;
    int position = block.position();
    int current = cursor.position() - block.position();
    for (int index = 0; index < brackets.size(); ++index) {
        Resources::Bracket *bracket = brackets.at(index);
        int highlightable = (position + bracket->position);
        if (bracket->character == left) {
            if ((bracket->position == current) && this->left(left, right, block, index + 1, 0, true))
                highlight(highlightable);
            else if ((bracket->position == (current - 1)) && this->left(left, right, block, index + 1, 0, true))
                highlight(highlightable);
        } else if (bracket->character == right) {
            if ((bracket->position == current) && this->right(left, right, block, index - 1, 0, true))
                highlight(highlightable);
            else if ((bracket->position == (current - 1)) && this->right(left, right, block, index - 1, 0, true))
                highlight(highlightable);
        }
    }
}

bool BracketMatcher::right(const QChar left, const QChar right, QTextBlock block, int start, int skip, bool first)
{
    Block *data = static_cast<Block *>(block.userData());
    QList<Resources::Bracket *> brackets;
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
        } else if (bracket->character == left) {
            if (skip == 0) {
                highlight(position + bracket->position);
                return true;
            } else
                --skip;
        }
    }
    loop:
    block = block.previous();
    return block.isValid() ? this->right(left, right, block, 0, skip) : false;
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
