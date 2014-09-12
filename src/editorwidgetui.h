#ifndef EDITORWIDGETUI_H
#define EDITORWIDGETUI_H

#include <QAction>
#include <QComboBox>
#include <QLabel>
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include "utility.h"

class EditorWidgetUI : public QWidget
{
    Q_OBJECT
private:
    void prepare();
protected:
    static QIcon icon(const char *name) {
        return Utility::icon(name);
    }
    static QString translate(const char *key) {
        return Utility::translate("editor", key);
    }
protected:
    // Actions
    QAction *_close;
    QAction *_split_horizontal;
    QAction *_split_vertical;
    // Layouts
    QHBoxLayout *_hlayout;
    QVBoxLayout *_vlayout;
    // Widgets
    QLabel *_detail;
    QComboBox *_primary;
    QComboBox *_secondary;
    QToolBar *_toolbar_left;
    QToolBar *_toolbar_top;
public:
    explicit EditorWidgetUI(QWidget *parent = 0)
        : QWidget(parent) {
        prepare();
    }
    ~EditorWidgetUI() {
    }
public:
    inline QToolBar *toolbar() { return _toolbar_left; }
};

#endif // EDITORWIDGETUI_H
