#ifndef VPZ_APKSTUDIO_COMPONENTS_LINENUMBERS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_LINENUMBERS_HPP

#include <QColor>
#include <QPair>
#include <QWidget>

namespace VPZ {
namespace APKStudio {
namespace Components {

class Coder;

class LineNumbers : public QWidget
{
    Q_OBJECT
private:
    Coder *coder;
    QPair<QColor, QColor> colors;
protected:
    void paintEvent(QPaintEvent *event);
public:
    explicit LineNumbers(Coder *coder = 0);
    inline QColor background() { return colors.first; }
    inline void background(QColor color) { colors.first = color; }
    inline QColor foreground() { return colors.second; }
    inline void foreground(QColor color) { colors.second = color; }
    QSize sizeHint() const;
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_LINENUMBERS_HPP
