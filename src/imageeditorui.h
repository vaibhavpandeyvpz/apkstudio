#ifndef IMAGEEDITORUI_H
#define IMAGEEDITORUI_H

#include <QFile>
#include <QLabel>
#include <QScrollArea>

#include "flickcharm.h"
#include "settings.h"

class ImageEditorUI : public QScrollArea
{
    Q_OBJECT
private:
    void prepare();
protected:
    QLabel *_image;
    FlickCharm *_charm;
public:
    explicit ImageEditorUI(QWidget *parent = 0)
        : QScrollArea(parent) {
        prepare();
    }
    ~ImageEditorUI() {
    }
};

#endif // IMAGEEDITORUI_H
