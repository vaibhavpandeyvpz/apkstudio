#ifndef VPZ_APKSTUDIO_HELPERS_HIGHLIGHTER_HPP
#define VPZ_APKSTUDIO_HELPERS_HIGHLIGHTER_HPP

#include <QColor>
#include <QFile>
#include <QFont>
#include <QHash>
#include <QHashIterator>
#include <QIODevice>
#include <QPair>
#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QVariant>
#include <QVector>
#include <QXmlStreamReader>
#include "application.hpp"
#include "resources/constant.hpp"
#include "resources/variant.hpp"
#include "settings.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class Block : public QTextBlockUserData
{
public:
    QVector<Resources::Bracket *> brackets;
    QVector<QPair<int, int> > literals;
public:
    Block() { }
    void bracket(Resources::Bracket *);
    bool literal(int);
    void literal(int, int);
};

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT
private:
    QHash<QString, QVector<Resources::Highlight> > definitions;
    QString mode;
    QHash<QString, QTextCharFormat> theme;
private:
    void initialize();
    QVector<Resources::Highlight> parse(const QString &);
public:
    explicit Highlighter(QObject * = 0);
    explicit Highlighter(QTextDocument * = 0);
    void highlightBlock(const QString &);
    void setMode(const QString &);
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_HIGHLIGHTER_HPP
