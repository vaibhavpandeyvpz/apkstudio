#ifndef VPZ_APKSTUDIO_UTILITY_TEXT_HPP
#define VPZ_APKSTUDIO_UTILITY_TEXT_HPP

#include <QApplication>
#include "resources/constant.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class Text
{
public:
    static QString capitalize(const QString &, bool = false);
    static QString translate(const char *, const char *);
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_UTILITY_TEXT_HPP
