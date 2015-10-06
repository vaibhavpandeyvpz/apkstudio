#ifndef CODERHIGHLIGHTERDEFINITION_H
#define CODERHIGHLIGHTERDEFINITION_H

#include "macros.h"
#include <QMap>
#include <QRegularExpression>

AS_NAMESPACE_START

struct CoderHighlighterDefinitionEntry
{
    bool multiline;
    QString regex;
    QString style;
};

typedef QList<CoderHighlighterDefinitionEntry> CoderHighlighterDefinitionEntryList;

class CoderHighlighterDefinition
{
private:
    CoderHighlighterDefinitionEntryList _entries;
private:
    CoderHighlighterDefinitionEntry parse(const QString &key, const QString &value) const;
public:
    CoderHighlighterDefinition(const QString &path);
public:
    CoderHighlighterDefinition &operator <<(const CoderHighlighterDefinitionEntry &entry);
    CoderHighlighterDefinition &operator <<(const CoderHighlighterDefinitionEntryList &entries);
    CoderHighlighterDefinition &operator <<(const CoderHighlighterDefinition &definition);
    inline CoderHighlighterDefinitionEntryList entries() const { return _entries; }
};

AS_NAMESPACE_END

#endif // CODERHIGHLIGHTERDEFINITION_H
