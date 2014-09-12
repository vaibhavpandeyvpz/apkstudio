#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <QScrollBar>
#include <QKeyEvent>

#include "imageeditorui.h"

class ImageEditor : public ImageEditorUI
{
    Q_OBJECT
private:
    double _scale;
    QString _current;
    QString _original;
private:
    void zoom(const double);
protected:
    void keyPressEvent(QKeyEvent *);
public:
    explicit ImageEditor(QWidget *parent = 0)
        : ImageEditorUI(parent) {
        _scale = 1.0;
    }
    ~ImageEditor() {
    }
public:
    void center();
    void invalidate(double factor);
    inline bool open(const QString &path) { return open(QFile(path)); }
    bool open(const QFile &, const bool = false);
    inline bool replace(const QString &path) { return replace(QFile(path)); }
    inline bool replace(const QFile &file) { return open(file, true); }
    void revert();
    bool save();
    inline void zoomIn() { zoom(1.25); }
    inline void zoomOut() { zoom(0.8); }
};

#endif // IMAGEEDITOR_H
