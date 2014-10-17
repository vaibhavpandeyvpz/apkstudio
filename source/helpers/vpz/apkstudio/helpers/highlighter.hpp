#ifndef VPZ_APKSTUDIO_HELPERS_HIGHLIGHTER_HPP
#define VPZ_APKSTUDIO_HELPERS_HIGHLIGHTER_HPP

#include <QSyntaxHighlighter>

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit Highlighter(QTextDocument *parent = 0);
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_HIGHLIGHTER_HPP
