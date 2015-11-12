#include <QFile>
#include <QRegularExpression>
#include "include/constants.h"
#include "include/coderhighlightertheme.h"
#include "include/fileutils.h"

APP_NAMESPACE_START

CoderHighlighterTheme::CoderHighlighterTheme(const QString &p)
{
    QString contents = FileUtils::read(p);
    QStringList lines = contents.split(QRegularExpression(REGEX_LF), QString::SkipEmptyParts);
    foreach (const QString l, lines)
    {
        QStringList p = l.split(QRegularExpression("\\s*=\\s*"), QString::SkipEmptyParts);
        if (p.size() == 2)
        {
            _styles.insert(p[0], parse(p[1]));
        }
    }
}

QTextCharFormat CoderHighlighterTheme::parse(const QString &s)
{
    QTextCharFormat tcf;
    QRegularExpression r(REGEX_THEME_STYLE);
    QRegularExpressionMatch m = r.match(s);
    while (m.hasMatch())
    {
        QString k = m.captured(1);
        QString v = m.captured(2);
        if (QString::compare(k, "background") == 0)
        {
            tcf.setBackground(QColor(v));
        }
        else if (QString::compare(k, "bold") == 0)
        {
            tcf.setFontWeight(QString::compare(v, "true") == 0 ? QFont::Bold : QFont::Normal);
        }
        else if (QString::compare(k, "foreground") == 0)
        {
            tcf.setForeground(QColor(v));
        }
        else if (QString::compare(k, "italics") == 0)
        {
            tcf.setFontItalic(QString::compare(v, "true") == 0);
        }
        else if (QString::compare(k, "underline") == 0)
        {
            tcf.setFontUnderline(QString::compare(v, "true") == 0);
        }
        m = r.match(s, m.capturedStart() + m.capturedLength());
    }
    return tcf;
}

APP_NAMESPACE_END
