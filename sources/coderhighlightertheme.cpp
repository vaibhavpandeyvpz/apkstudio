#include <QFile>
#include <QRegularExpression>
#include <QTextStream>
#include "constants.h"
#include "coderhighlightertheme.h"

AS_NAMESPACE_START

CoderHighlighterTheme::CoderHighlighterTheme(const QString &p)
{
    QFile file(p);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in.setCodec(ENCODING_DEFAULT);
        while (!in.atEnd())
        {
            QString l = in.readLine();
            if (!l.isNull() && !l.isEmpty())
            {
                QStringList p = l.split(QRegularExpression("\\s*=\\s*"), QString::SkipEmptyParts);
                if (p.size() == 2)
                {
                    _styles.insert(p[0], parse(p[1]));
                }
            }
        }
        file.close();
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

AS_NAMESPACE_END
