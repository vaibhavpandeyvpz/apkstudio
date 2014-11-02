#ifndef VPZ_APKSTUDIO_RESOURCES_EMBEDDED_HPP
#define VPZ_APKSTUDIO_RESOURCES_EMBEDDED_HPP

#include <QIcon>
#include "constant.hpp"

extern "C" {
    inline QIcon icon(const QString &name) { return QIcon(QString(RESOURCE_PATH_ICON).append(name).append(".png")); }
}

#endif // VPZ_APKSTUDIO_RESOURCES_EMBEDDED_HPP
