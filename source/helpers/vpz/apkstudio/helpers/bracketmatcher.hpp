#ifndef VPZ_APKSTUDIO_HELPERS_BRACKETMATCHER_HPP
#define VPZ_APKSTUDIO_HELPERS_BRACKETMATCHER_HPP

#include <QPlainTextEdit>
#include <QTextBlock>
#include <QTextCharFormat>
#include "resources/variant.hpp"
#include "highlighter.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class BracketMatcher
{
private:
    QColor color;
    QPlainTextEdit *editor;
private:
    void highlight(const int);
    bool left(const QChar, const QChar, QTextBlock, int, int);
    bool right(const QChar, const QChar, QTextBlock, int, int, bool = false);
public:
    BracketMatcher(QPlainTextEdit *, const QString &);
    void match(const QChar, const QChar);
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_BRACKETMATCHER_HPP
