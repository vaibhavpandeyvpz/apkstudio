#ifndef EDITORTABS_H
#define EDITORTABS_H

#include <QFileIconProvider>
#include <QMap>
#include <QPointer>
#include <QTabWidget>
#include "macros.h"

APP_NAMESPACE_START

class FindReplace;

class EditorTabs : public QTabWidget
{
    Q_OBJECT
private:
    APP_CONNECTIONS_LIST
    QMap<QString, int> _files;
    QPointer<FindReplace> _finder;
    QFileIconProvider _provider;
public:
    explicit EditorTabs(QWidget *parent = 0);
    ~EditorTabs();
private Q_SLOTS:
    void onCurrentChanged(const int index);
    void onFileClose();
    void onFileCloseAll();
    void onEditCopy();
    void onEditCut();
    void onEditFind();
    void onEditGoto();
    void onEditPaste();
    void onEditRedo();
    void onEditReplace();
    void onEditUndo();
    void onFileOpen(const QString &path);
    void onFileSave();
    void onFileSave(const int i);
    void onFileSaveAll();
    void onTabCloseRequested(const int index);
    void onTabMoved(const int from, const int to);
Q_SIGNALS:
    void fileChanged(QString);
    void fileSaved(QString);
};

APP_NAMESPACE_END

#endif // EDITORTABS_H
