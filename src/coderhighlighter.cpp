#include "include/coderhighlighter.h"
#include "include/constants.h"
#include "include/preferences.h"

APP_NAMESPACE_START

CoderHighlighter::CoderHighlighter(const QString &d, const QString &t, QTextDocument *doc)
    : QSyntaxHighlighter(doc)
{
    _definition = new CoderHighlighterDefinition(QString(QRC_HIGHLIGHT).arg(d));
    _theme = new CoderHighlighterTheme(QString(QRC_HIGHLIGHT).arg(t));
    if (Preferences::get()->showWhitespaces())
    {
        CoderHighlighterDefinitionEntry e;
        e.regex = REGEX_WHITESPACE;
        e.style = HIGHLIGHTER_STYLE_WHITESPACES;
        *_definition << e;
    }
}

void CoderHighlighter::highlightBlock(const QString &t)
{
    foreach (const CoderHighlighterDefinitionEntry &d, _definition->entries())
    {
        if (!d.regex.isNull() && !d.regex.isEmpty())
        {
            if (d.multiline)
            {
                QStringList p = d.regex.split('|');
                QRegularExpression br(p.first());
                QRegularExpression er(p.last());
                setCurrentBlockState(0);
                int b = 0;
                if (previousBlockState() != 1)
                {
                    b = br.match(t).capturedStart();
                }
                while (b >= 0)
                {
                    QRegularExpressionMatch m = er.match(t, b);
                    int e = m.capturedStart();
                    int l;
                    if (e == -1)
                    {
                        setCurrentBlockState(1);
                        l = (t.length() - b);
                    }
                    else
                    {
                        l = ((e - b) + m.capturedLength());
                    }
                    setFormat(b, l, _theme->styles().value(d.style));
                    b = br.match(t, (b + l)).capturedStart();
                }
            }
            else
            {
                QRegularExpression r(d.regex);
                QRegularExpressionMatch m = r.match(t);
                while (m.hasMatch())
                {
                    int i = m.capturedStart();
                    int l = m.capturedLength();
                    setFormat(i, l, _theme->styles().value(d.style));
                    m = r.match(t, i + l);
                }
            }
        }
    }
}

CoderHighlighter::~CoderHighlighter()
{
    delete _definition;
    delete _theme;
}

APP_NAMESPACE_END
