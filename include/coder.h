#ifndef CODER_H
#define CODER_H

#include <QCompleter>
#include <QPlainTextEdit>
#include <QPointer>
#include <QTextBlock>
#include <QTimer>
#include "macros.h"

APP_NAMESPACE_START

class CoderSidebar;

class CoderHighlighter;

class Coder : public QPlainTextEdit
{
    Q_OBJECT
private:
    APP_CONNECTIONS_LIST
    CoderSidebar *_sidebar;
    bool _spacesForTabs;
    int _tabStopWidth;
private:
    QString addIndent(QString text, int count);
    int indentSize(const QString &text);
    bool indentText(const bool forward = true);
    void moveLine(const bool up);
    void transformTo(const bool upper);
private Q_SLOTS:
    void onMoveLineDown();
    void onMoveLineUp();
    void onCursorPositionChanged();
    void onInit();
    void onUpdateRequest(const QRect &rect, const int column);
    void onUpdateMargins(const int count);
    void onTransformToLower();
    void onTransformToUpper();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    bool event(QEvent *event);
    void focusInEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);
public:
    explicit Coder(QWidget *parent = 0);
    QTextCursor currentTextCursor() const;
    int currentColumn() const;
    int currentRow() const;
    inline QRectF getBlockBoundingRect(const QTextBlock &block)
    {
        return blockBoundingRect(block);
    }
    inline QRectF getBlockBoundingGeometry(const QTextBlock &block)
    {
        return blockBoundingGeometry(block);
    }
    inline QPointF getContentOffset()
    {
        return contentOffset();
    }
    inline QTextBlock getFirstVisibleBlock()
    {
        return firstVisibleBlock();
    }
    void gotoLineEnd();
    void gotoLineStart();
    void setCompleter(QCompleter *completer);
    void setCurrentRow(const int row);
    void setFont(const QFont &font);
    void setTabStopWidth(const int width);
    ~Coder();
Q_SIGNALS:
    void fileDropped(const QString &path);
    void tooltipRequested(const QPoint &position);
};

APP_NAMESPACE_END

#endif // CODER_H
