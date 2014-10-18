#ifndef VPZ_APKSTUDIO_HELPERS_APPLICATION_HPP
#define VPZ_APKSTUDIO_HELPERS_APPLICATION_HPP

#include <QApplication>
#include <QFile>
#include <QHash>
#include <QIODevice>
#include <QTextCharFormat>
#include <QVariant>
#include <QXmlStreamReader>
#include "resources/constant.hpp"
#include "resources/variant.hpp"
#include "settings.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class Application : public QApplication
{
    Q_OBJECT
public:
#ifdef Q_QDOC
    Application(int &, char **);
#else
    Application(int &, char **, int = ApplicationFlags);
#endif
    static QList<Resources::Style> theme();
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_APPLICATION_HPP
