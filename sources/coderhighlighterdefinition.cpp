#include <QFile>
#include <QTextStream>
#include "constants.h"
#include "coderhighlighterdefinition.h"

AS_NAMESPACE_START

CoderHighlighterDefinition::CoderHighlighterDefinition(const QString &p)
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
                QStringList p = l.split(QRegularExpression(REGEX_WHITESPACE), QString::SkipEmptyParts);
                if (p.size() == 2)
                {
                    if (QString::compare(p[0], "@include") == 0)
                    {
                        *this << CoderHighlighterDefinition(QString(QRC_HIGHLIGHT).arg(p[1]));
                    }
                    else
                    {
                        *this << parse(p[0], p[1]);
                    }
                }
            }
        }
        file.close();
    }
}

CoderHighlighterDefinitionEntry CoderHighlighterDefinition::parse(const QString &k, const QString &v) const
{
    CoderHighlighterDefinitionEntry hde;
    if (k.contains('#'))
    {
        QStringList p = k.split('#', QString::SkipEmptyParts);
        hde.style = p[0];
        if ((p.size() == 2) && (QString::compare(p[1], "multiline") == 0))
        {
            hde.multiline = true;
        }
    }
    else
    {
        hde.style = k;
    }
    hde.regex = v;
    return hde;
}

CoderHighlighterDefinition &CoderHighlighterDefinition::operator <<(const CoderHighlighterDefinition &hd)
{
    _entries << hd.entries();
    return *this;
}

CoderHighlighterDefinition &CoderHighlighterDefinition::operator <<(const CoderHighlighterDefinitionEntry &hde)
{
    _entries << hde;
    return *this;
}

CoderHighlighterDefinition &CoderHighlighterDefinition::operator <<(const CoderHighlighterDefinitionEntryList &hdel)
{
    _entries << hdel;
    return *this;
}

AS_NAMESPACE_END
