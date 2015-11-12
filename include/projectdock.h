#ifndef PROJECTDOCK_H
#define PROJECTDOCK_H

#include <QDockWidget>
#include <QFileIconProvider>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include "macros.h"

APP_NAMESPACE_START

class ProjectDock : public QDockWidget
{
    Q_OBJECT
private:
    APP_CONNECTIONS_LIST
    QFileIconProvider _fip;
    QTreeWidget *_tree;
private:
    void onItemRefresh(QTreeWidgetItem *item);
public:
    enum ProjectDockRole
    {
        RoleType = Qt::UserRole + 1,
        RolePath
    };
    enum ProjectDockType
    {
        TypeProject = 100,
        TypeDir,
        TypeFile
    };
public:
    explicit ProjectDock(QWidget *parent = 0);
    ~ProjectDock();
private Q_SLOTS:
    void onDoubleClicked(const QModelIndex &index);
    void onProjectOpen(const QString &path);
    void onProjectReload();
Q_SIGNALS:
    void fileOpen(QString);
};

APP_NAMESPACE_END

Q_DECLARE_METATYPE(APP_NAMESPACE::ProjectDock::ProjectDockType)

#endif // PROJECTDOCK_H
