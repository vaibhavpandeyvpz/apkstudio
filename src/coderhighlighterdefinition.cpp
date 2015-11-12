#include <QFile>
#include "include/constants.h"
#include "include/coderhighlighterdefinition.h"
#include "include/fileutils.h"

APP_NAMESPACE_START

CoderHighlighterDefinition::CoderHighlighterDefinition(const QString &p)
{
    QString contents = FileUtils::read(p);
    QStringList lines = contents.split(QRegularExpression(REGEX_LF), QString::SkipEmptyParts);
    foreach (const QString l, lines)
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

APP_NAMESPACE_END
