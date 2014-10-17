#ifndef VPZ_APKSTUDIO_COMPONENTS_CODER_HPP
#define VPZ_APKSTUDIO_COMPONENTS_CODER_HPP

#include <QPlainTextEdit>

namespace VPZ {
namespace APKStudio {
namespace Components {

class Coder : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit Coder(QWidget *parent = 0);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_CODER_HPP
