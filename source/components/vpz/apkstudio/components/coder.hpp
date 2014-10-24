#ifndef VPZ_APKSTUDIO_COMPONENTS_CODER_HPP
#define VPZ_APKSTUDIO_COMPONENTS_CODER_HPP

#include <QAction>
#include <QHash>
#include <QHelpEvent>
#include <QKeyEvent>
#include <QMenu>
#include <QPair>
#include <QPainter>
#include <QPaintEvent>
#include <QPlainTextEdit>
#include <QTextBlock>
#include <QTextCharFormat>
#include <QTimer>
#include <QToolTip>
#include <QWidget>
#include "helpers/application.hpp"
#include "helpers/bracketmatcher.hpp"
#include "helpers/highlighter.hpp"
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "resources/variant.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class LineNumbers;

class Coder : public QPlainTextEdit
{
    Q_OBJECT
private:
    Helpers::BracketMatcher *brackets_matcher;
    Helpers::Highlighter *highlighter;
    QList<QMetaObject::Connection> connections;
    QPair<int, int> cache;
    LineNumbers *line_numbers;
    Resources::Theme theme;
private:
    bool indent();
    static QString translate(const char *key) {
        return Helpers::Text::translate("coder", key);
    }
private Q_SLOTS:
    void onBlockCountChanged(const int);
    void onCursorPositionChanged();
    void onUpdateRequest(const QRect &, const int);
public:
    explicit Coder(QWidget *parent = 0);
    bool event(QEvent *);
    void keyPressEvent(QKeyEvent *);
    inline void mode(const QString &definition) { highlighter->mode(definition); }
    inline QString mode() { return highlighter->mode(); }
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void setFont(const QFont &);
public:
    inline QRectF getBlockBoundingRect(const QTextBlock &block) { return blockBoundingRect(block); }
    inline QRectF getBlockBoundingGeometry(const QTextBlock &block) { return blockBoundingGeometry(block); }
    inline QTextBlock getFirstVisibleBlock() { return firstVisibleBlock(); }
    inline QPointF getContentOffset() { return contentOffset(); }
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_CODER_HPP
