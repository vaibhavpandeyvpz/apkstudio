#ifndef CODERHIGHLIGHTERTHEME_H
#define CODERHIGHLIGHTERTHEME_H

#include <QMap>
#include <QTextCharFormat>
#include "macros.h"

APP_NAMESPACE_START

typedef QMap<QString, QTextCharFormat> CoderHighlighterThemeStyles;

class CoderHighlighterTheme
{
private:
    CoderHighlighterThemeStyles _styles;
private:
    QTextCharFormat parse(const QString &style);
public:
    CoderHighlighterTheme(const QString &path);
    inline CoderHighlighterThemeStyles styles() const { return _styles; }
};

APP_NAMESPACE_END

#endif // CODERHIGHLIGHTERTHEME_H
