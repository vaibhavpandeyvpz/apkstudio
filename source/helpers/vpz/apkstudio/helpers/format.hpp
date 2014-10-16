#ifndef VPZ_APKSTUDIO_HELPERS_FORMAT_HPP
#define VPZ_APKSTUDIO_HELPERS_FORMAT_HPP

#include <QApplication>
#include <QDateTime>
#include "resources/constant.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class Format
{
public:
    static QString size(float bytes);
    static QString timestamp(const QDateTime & = QDateTime::currentDateTime(), const QString & = FORMAT_TIMESTAMP_GENERAL);
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_FORMAT_HPP
