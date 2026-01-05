#include <QFile>
#include <QSettings>
#include <QRegularExpression>
#include <QTextStream>
#include "themedsyntaxhighlighter.h"

#define REGEXP_CRLF "[\\r\\n]"
#define REGEXP_THEME_LINE "\\s*=\\s*"
#define REGEXP_THEME_STYLE "\\b([a-z]+)\\:\\s*([0-9a-z#]+)\\b"
#define REGEXP_WHITESPACE "[\\s\\t]+"

ThemedSyntaxHighlighter::ThemedSyntaxHighlighter(const SyntaxHighlighterTheme &theme, const SyntaxHighlighterDefinitionList &definitions, QTextDocument *document)
    : QSyntaxHighlighter(document), m_Definitions(definitions), m_Theme(theme)
{
}

void ThemedSyntaxHighlighter::highlightBlock(const QString &text) {
    foreach (const SyntaxHighlighterDefinition &definition, m_Definitions) {
        if (definition.regexp.isEmpty()) {
            continue;
        }
        if (definition.multiline) {
            QStringList pair = definition.regexp.split('|');
            QRegularExpression fregexp(pair.first());
            QRegularExpression eregexp(pair.last());
            setCurrentBlockState(0);
            int i = 0;
            if (previousBlockState() != 1) {
                i = text.indexOf(fregexp);
            }
            while (i >= 0) {
                QRegularExpressionMatch match = eregexp.match(text, i);
                int j = match.capturedStart();
                int length;
                if (j == -1) {
                    setCurrentBlockState(1);
                    length = (text.length() - i);
                } else {
                    length = ((j - i) + match.capturedLength());
                }
                setFormat(i, length, m_Theme.value(definition.style));
                i = text.indexOf(fregexp, i + length);
            }
            continue;
        }
        QRegularExpression regexp(definition.regexp);
        QRegularExpressionMatchIterator iterator = regexp.globalMatch(text);
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), m_Theme.value(definition.style));
        }
    }
}

SyntaxHighlighterDefinitionList ThemedSyntaxHighlighter::definitions(const QString &language)
{
    SyntaxHighlighterDefinitionList defs;
    QFile file(QString(":/highlights/%1.def").arg(language));
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream contents(&file);
        QString data = contents.readAll();
        file.close();
        QStringList lines = data.split(QRegularExpression(REGEXP_CRLF), Qt::SkipEmptyParts);
        foreach (const QString line, lines) {
            QStringList pair = line.split(QRegularExpression(REGEXP_WHITESPACE), Qt::SkipEmptyParts);
            if (pair.size() == 2) {
                if (QString::compare(pair.first(), "@include") == 0) {
                    defs << definitions(pair.last());
                } else {
                    SyntaxHighlighterDefinition def;
                    def.style = pair.first();
                    def.multiline = def.style.endsWith('?');
                    if (def.multiline) {
                        def.style = def.style.mid(0, def.style.length() - 1);
                    }
                    def.regexp = pair.last();
                    defs << def;
                }
            }
        }
    }
    QSettings settings;
    const bool whitespaces = settings.value("editor_whitespaces", false).toBool();
    if (whitespaces) {
        SyntaxHighlighterDefinition def;
        def.multiline = false;
        def.regexp = REGEXP_WHITESPACE;
        def.style = "whitespaces";
        defs << def;
    }
    return defs;
}

SyntaxHighlighterTheme ThemedSyntaxHighlighter::theme(const QString &name)
{
    SyntaxHighlighterTheme theme;
    QFile file(QString(":/themes/%1.theme").arg(name));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream contents(&file);
        QString data = contents.readAll();
        file.close();
        QStringList lines = data.split(QRegularExpression(REGEXP_CRLF), Qt::SkipEmptyParts);
        foreach (const QString line, lines) {
            QStringList pair = line.split(QRegularExpression(REGEXP_THEME_LINE), Qt::SkipEmptyParts);
            if (pair.size() == 2) {
                QTextCharFormat tcf;
                QRegularExpression regexp(REGEXP_THEME_STYLE);
                QRegularExpressionMatch match = regexp.match(pair[1]);
                while (match.hasMatch()) {
                    QString key = match.captured(1);
                    QString value = match.captured(2);
                    if (QString::compare(key, "background") == 0) {
                        tcf.setBackground(QColor(value));
                    } else if (QString::compare(key, "bold") == 0) {
                        tcf.setFontWeight(QString::compare(value, "true") == 0 ? QFont::Bold : QFont::Normal);
                    } else if (QString::compare(key, "foreground") == 0) {
                        tcf.setForeground(QColor(value));
                    } else if (QString::compare(key, "italics") == 0) {
                        tcf.setFontItalic(QString::compare(value, "true") == 0);
                    } else if (QString::compare(key, "underline") == 0) {
                        tcf.setFontUnderline(QString::compare(value, "true") == 0);
                    }
                    match = regexp.match(pair.last(), match.capturedStart() + match.capturedLength());
                }
                theme.insert(pair.first(), tcf);
            }
        }
    }
    return theme;
}
