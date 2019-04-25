#ifndef SOURCECODEEDIT_H
#define SOURCECODEEDIT_H

#include <QPlainTextEdit>

class SourceCodeSidebarWidget;

class SourceCodeEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit SourceCodeEdit(QWidget *parent = nullptr);
    QRectF blockBoundingGeometryProxy(const QTextBlock &block);
    QRectF blockBoundingRectProxy(const QTextBlock &block);
    QPointF contentOffsetProxy();
    QString filePath();
    QTextBlock firstVisibleBlockProxy();
    void gotoLine(const int no);
    void moveCursor(const bool end);
    void open(const QString &path);
    bool save();
protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
    QString m_FilePath;
    SourceCodeSidebarWidget *m_Sidebar;
    int indentSize(const QString &text);
    bool indentText(const bool forward);
    QString indentText(QString text, int count) const;
    void moveSelection(const bool up);
    void transformText(const bool upper);
private slots:
    void handleBlockCountChanged(const int count);
    void handleCursorPositionChanged();
    void handleUpdateRequest(const QRect &rect, const int column);
    void handleTextChanged();
};

class SourceCodeSidebarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SourceCodeSidebarWidget(SourceCodeEdit *edit);
    QSize sizeHint() const;
protected:
    void leaveEvent(QEvent *event);
    void mouseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
    SourceCodeEdit *m_Edit;
};

#endif // SOURCECODEEDIT_H
