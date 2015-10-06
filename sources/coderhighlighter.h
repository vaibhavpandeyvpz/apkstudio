#ifndef CODERHIGHLIGHTER_H
#define CODERHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include "coderhighlighterdefinition.h"
#include "coderhighlightertheme.h"
#include "macros.h"

AS_NAMESPACE_START

class CoderHighlighter : public QSyntaxHighlighter
{
private:
    CoderHighlighterDefinition *_definition;
    bool _showWhitespaces;
    CoderHighlighterTheme *_theme;
public:
    explicit CoderHighlighter(const QString &definition, const QString &theme, QTextDocument *document = 0);
    ~CoderHighlighter();
    void highlightBlock(const QString &text);
};

AS_NAMESPACE_END

#endif // CODERHIGHLIGHTER_H
