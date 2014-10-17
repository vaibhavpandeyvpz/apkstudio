#ifndef VPZ_APKSTUDIO_HELPERS_COMPLETER_HPP
#define VPZ_APKSTUDIO_HELPERS_COMPLETER_HPP

#include <QCompleter>

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class Completer : public QCompleter
{
    Q_OBJECT
public:
    explicit Completer(QObject *parent = 0);
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_COMPLETER_HPP
