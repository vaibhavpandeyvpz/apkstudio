#ifndef THEMEDSYNTAXHIGHLIGHTER_H
#define THEMEDSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

struct SyntaxHighlighterDefinition
{
    bool multiline;
    QString regexp;
    QString style;
};

typedef QList<SyntaxHighlighterDefinition> SyntaxHighlighterDefinitionList;

typedef QMap<QString, QTextCharFormat> SyntaxHighlighterTheme;

class ThemedSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    explicit ThemedSyntaxHighlighter(const SyntaxHighlighterTheme &theme, const SyntaxHighlighterDefinitionList &definitions, QTextDocument *document = nullptr);
    static SyntaxHighlighterDefinitionList definitions(const QString &language);
    static SyntaxHighlighterTheme theme(const QString &name);
    void highlightBlock(const QString &text);
private:
    SyntaxHighlighterDefinitionList m_Definitions;
    SyntaxHighlighterTheme m_Theme;
};

#endif // THEMEDSYNTAXHIGHLIGHTER_H
