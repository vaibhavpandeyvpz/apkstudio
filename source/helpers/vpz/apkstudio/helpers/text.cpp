#include "text.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

QString Text::capitalize(const QString &text, bool strict)
{
    QString temporary = text;
    if (strict)
        temporary = text.toLower();
    temporary[0] = temporary[0].toUpper();
    return temporary;
}

QString Text::translate(const char *context, const char *key)
{
    return QApplication::translate(context, key);
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
