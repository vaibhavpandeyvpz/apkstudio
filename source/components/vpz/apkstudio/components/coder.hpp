#ifndef VPZ_APKSTUDIO_COMPONENTS_CODER_HPP
#define VPZ_APKSTUDIO_COMPONENTS_CODER_HPP

#include <QHash>
#include <QKeyEvent>
#include <QPlainTextEdit>
#include "helpers/application.hpp"
#include "helpers/settings.hpp"
#include "resources/variant.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Coder : public QPlainTextEdit
{
    Q_OBJECT
private:
    QHash<QString, QString> theme;
private:
    void cursorPositionChanged();
private Q_SLOTS:
    void highlightCurrentLine();
public:
    explicit Coder(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_CODER_HPP
