#ifndef VPZ_APKSTUDIO_COMPONENTS_CODER_HPP
#define VPZ_APKSTUDIO_COMPONENTS_CODER_HPP

#include <QHash>
#include <QHelpEvent>
#include <QKeyEvent>
#include <QPair>
#include <QPainter>
#include <QPaintEvent>
#include <QPlainTextEdit>
#include <QTextBlock>
#include <QTextCharFormat>
#include <QToolTip>
#include <QWidget>
#include "helpers/application.hpp"
#include "helpers/bracketmatcher.hpp"
#include "helpers/highlighter.hpp"
#include "helpers/settings.hpp"
#include "resources/variant.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class LineNumbers;

class Coder : public QPlainTextEdit
{
    Q_OBJECT
private:
    Helpers::BracketMatcher *bracket_matcher;
    QPair<int, int> cache;
    LineNumbers *line_numbers;
    Resources::Theme theme;
private Q_SLOTS:
    void onBlockCountChanged(const int);
    void onCursorPositionChanged();
    void onUpdateRequest(const QRect &, const int);
public:
    explicit Coder(QWidget *parent = 0);
    bool event(QEvent* event);
    void highlightBracket(int, int);
    void keyPressEvent(QKeyEvent *);
    int lineNumbersAreaWidth();
    void lineNumbersPaintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
};

class LineNumbers : public QWidget
{
    Q_OBJECT
private:
    Coder *coder;
protected:
    void paintEvent(QPaintEvent *event) {
        coder->lineNumbersPaintEvent(event);
    }
public:
    explicit LineNumbers(Coder *coder = 0) : QWidget(coder) {
        this->coder = coder;
    }
    QSize sizeHint() const {
        return QSize(coder->lineNumbersAreaWidth(), 0);
    }
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_CODER_HPP
