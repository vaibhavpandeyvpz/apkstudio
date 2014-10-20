#ifndef VPZ_APKSTUDIO_COMPONENTS_CODER_HPP
#define VPZ_APKSTUDIO_COMPONENTS_CODER_HPP

#include <QHash>
#include <QKeyEvent>
#include <QPair>
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

    QPair<int, int> cache;
    LineNumbers *linenumbers;
    Resources::Theme theme;
private Q_SLOTS:
    void onBlockCountChanged(const int);
    void onCursorPositionChanged();
    void onUpdateRequest(const QRect &, const int);
public:
    explicit Coder(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *);
    int lineNumbersAreaWidth();
    void lineNumbersPaintEvent(QPaintEvent *);
};

class LineNumbers : public QWidget
{
    Q_OBJECT
private:
    Coder *coder;
protected:
    void paintEvent(QPaintEvent *);
public:
    explicit LineNumbers(Coder *coder = 0);
    QSize sizeHint() const;
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_CODER_HPP
