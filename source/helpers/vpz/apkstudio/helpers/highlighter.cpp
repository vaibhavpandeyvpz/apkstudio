#include "highlighter.hpp"
#include <QDebug>

namespace VPZ {
namespace APKStudio {
namespace Helpers {

Highlighter::Highlighter(QObject *parent) :
    QSyntaxHighlighter(parent), mode("java")
{
    initialize();
}

Highlighter::Highlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent), mode("java")
{
    initialize();
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const Resources::Highlight &rule, definitions.value(mode)) {
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
                    length = text.length() - start;
                } else
                    length = stop - start + matcher.capturedLength();
                setFormat(start, length, multiline);
                start = begin.match(text, start + length).capturedStart();
            }
            continue;
        }
        QRegularExpression expression(rule.regex);
        QRegularExpressionMatch matcher = expression.match(text);
        while (matcher.hasMatch()) {
            int index = matcher.capturedStart();
            int length = matcher.capturedLength();
            setFormat(index, length, theme.value(rule.style));
            matcher = expression.match(text, index + length);
        }
    }
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

void Highlighter::setMode(const QString &mode)
{
    this->mode = mode;
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
