#ifndef PROJECTDOCK_H
#define PROJECTDOCK_H

#include <QDockWidget>
#include <QFileIconProvider>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include "macros.h"

AS_NAMESPACE_START

class ProjectDock : public QDockWidget
{
    Q_OBJECT
private:
    AS_CONNECTIONS_LIST
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
private slots:
    void onDoubleClicked(const QModelIndex &index);
    void onProjectOpen(const QString &path);
    void onProjectReload();
signals:
    void fileOpen(QString);
};

AS_NAMESPACE_END

Q_DECLARE_METATYPE(As::ProjectDock::ProjectDockType)

#endif // PROJECTDOCK_H
