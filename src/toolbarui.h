#ifndef TOOLBARUI_H
#define TOOLBARUI_H

#include <QAction>
#include <QComboBox>
#include <QToolBar>

#include "settings.h"
#include "utility.h"

class ToolBarUI : public QToolBar
{
    Q_OBJECT
private:
    void prepare();
private Q_SLOTS:
    void onEncodingSelected(const int);
protected:
    // Actions
    QAction *_build;
    QAction *_clean;
    QAction *_first;
    QAction *_full_screen;
    QAction *_last;
    QAction *_new;
    QAction *_next;
    QAction *_open;
    QAction *_previous;
    QAction *_save;
    QAction *_save_all;
    QAction *_terminal;
    QAction *_windowed;
    // ComboBoxes
    QComboBox *_encoding;
protected:
    static QIcon icon(const char *name) {
        return Utility::icon(name);
    }
    static QString translate(const char *key) {
        return Utility::translate("toolbar", key);
    }
public:
    explicit ToolBarUI(QWidget *parent = 0)
        : QToolBar(parent) {
        prepare();
    }
    ~ToolBarUI() {
    }
};

#endif // TOOLBARUI_H
