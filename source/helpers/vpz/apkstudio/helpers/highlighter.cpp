#include "highlighter.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

void Block::bracket(Resources::Bracket *bracket)
{
    int index = 0;
    while ((index < brackets.size()) && (bracket->position > brackets.at(index)->position))
        ++index;
    brackets.insert(index, bracket);
}

bool Block::literal(int column)
{
    QPair<int, int> literal;
    foreach (literal, literals) {
        if ((column > literal.first) && (column < literal.second))
            return true;
    }
    return false;
}

void Block::literal(int line, int column)
{
    literals.append(QPair<int, int>(line, column));
}

Highlighter::Highlighter(QObject *parent) :
    QSyntaxHighlighter(parent), definition("java")
{
    initialize();
}

Highlighter::Highlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent), definition("java")
{
    initialize();
}

void Highlighter::highlight(Block *block, const QString &text, const QString &name, const QString &regex)
{
    QStringList literals = QString("commentml|commentsl|string|stringb|stringul").split('|');
    QRegularExpression expression(regex);
    QRegularExpressionMatch matcher = expression.match(text);
    while (matcher.hasMatch()) {
        int index = matcher.capturedStart();
        int length = matcher.capturedLength();
        setFormat(index, length, theme.value(name));
        matcher = expression.match(text, index + length);
        if (!block && !literals.contains(name))
            continue;
        block->literal(index, (index + length));
    }
}

void Highlighter::highlightBlock(const QString &text)
{
    Block *block = new Block;
    foreach (const Resources::Highlight &rule, definitions.value(definition)) {
        if (rule.style == "commentml") {
            QTextCharFormat multiline = theme.value(rule.style);
            QStringList startstop = rule.regex.split('|');
            QRegularExpression begin(startstop.first());
            QRegularExpression end(startstop.last());
            setCurrentBlockState(0);
            int start = 0;
            if (previousBlockState() != 1)
                start = begin.match(text).capturedStart();
            while (start >= 0) {
                QRegularExpressionMatch matcher = end.match(text, start);
                int stop = matcher.capturedStart();
                int length;
                if (stop == -1) {
                    setCurrentBlockState(1);
                    length = (text.length() - start);
                } else
                    length = ((stop - start) + matcher.capturedLength());
                setFormat(start, length, multiline);
                start = begin.match(text, (start + length)).capturedStart();
            }
            continue;
        }
        highlight(block, text, rule.style, rule.regex);
    }
    QStringList brackets = Settings::brackets();
    foreach (const QString &pair, brackets) {
        foreach (const QChar &character, pair) {
            int position = text.indexOf(character);
            while (position > -1) {
                Resources::Bracket *bracket;
                if (block->literal(position))
                    goto loop;
                bracket = new Resources::Bracket;
                bracket->character = character;
                bracket->position = position;
                block->bracket(bracket);
                loop:
                position = text.indexOf(character, position + 1);
            }
        }
    }
    setCurrentBlockUserData(block);
    if (Settings::showWhitespace())
        highlight(nullptr, text, "whitespace", "[\\s]");
}

void Highlighter::initialize()
{
    QStringList languages;
    languages << "java" << "smali" << "xml";
    foreach (const QString language, languages)
        definitions.insert(language, parse(language));
    Resources::Theme styles = Application::theme();
    Resources::Theme::iterator iterator;
    for (iterator = styles.begin(); iterator != styles.end(); iterator++) {
        Resources::Style style = iterator.value();
        QTextCharFormat format;
        if (style.bold)
            format.setFontWeight(QFont::Bold);
        format.setFontItalic(style.italic);
        format.setFontUnderline(style.underline);
        format.setForeground(QColor(style.color));
        theme.insert(iterator.key(), format);
    }
}

QVector<Resources::Highlight> Highlighter::parse(const QString &name)
{
    QVector<Resources::Highlight> ruleset;
    QFile *xml = new QFile(QString(RESOURCE_PATH_HIGHLIGHT).append(name).append(".xml"));
    if (xml->exists() && xml->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader reader(xml);
        Resources::Highlight highlight;
        while (!reader.atEnd() && !reader.hasError()) {
            QXmlStreamReader::TokenType type = reader.readNext();
            if (type == QXmlStreamReader::StartDocument)
                continue;
            if (type != QXmlStreamReader::StartElement)
                continue;
            QString tag = reader.name().toString();
            if ((tag == "definition") || !((tag == "include") || (tag == "rule")))
                continue;
            QXmlStreamAttributes attributes = reader.attributes();
            if ((tag == "include") && attributes.hasAttribute("definition")) {
                QVector<Resources::Highlight> subset = parse(attributes.value("definition").toString());
                if (!subset.isEmpty()) {
                    foreach (const Resources::Highlight &rule, subset)
                        ruleset.append(rule);
                }
                continue;
            }
            if (!attributes.hasAttribute("style"))
                continue;
            highlight.style = attributes.value("style").toString();
            highlight.regex = reader.readElementText().trimmed();
            ruleset.append(highlight);
        }
        reader.clear();
        xml->close();
    }
    return ruleset;
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
