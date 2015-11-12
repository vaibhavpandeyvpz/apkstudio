#include <QDir>
#include <QFileIconProvider>
#include <QHeaderView>
#include "include/preferences.h"
#include "include/projectdock.h"
#include "include/qrc.h"

APP_NAMESPACE_START

ProjectDock::ProjectDock(QWidget *p)
    : QDockWidget(__("project", "docks"), p)
{
    _connections << connect(this, SIGNAL(fileOpen(QString)), p, SLOT(onFileOpen(QString)));
    _connections << connect(p, SIGNAL(projectOpen(QString)), this, SLOT(onProjectOpen(QString)));
    _connections << connect(p, SIGNAL(projectReload()), this, SLOT(onProjectReload()));
    _tree = new QTreeWidget(this);
    _tree->header()->hide();
    _tree->setContextMenuPolicy(Qt::CustomContextMenu);
    _tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _tree->setSelectionBehavior(QAbstractItemView::SelectItems);
    _tree->setSelectionMode(QAbstractItemView::SingleSelection);
    _tree->setSortingEnabled(false);
    _connections << connect(_tree, &QTreeWidget::doubleClicked, this, &ProjectDock::onDoubleClicked);
    setObjectName("ProjectDock");
    setWidget(_tree);
}

void ProjectDock::onDoubleClicked(const QModelIndex &i)
{
    int t = i.data(RoleType).toInt();
    if (t == TypeFile)
    {
        QString p = i.data(RolePath).toString();
        if (!p.isEmpty())
        {
            emit fileOpen(p);
        }
    }
}

void ProjectDock::onItemRefresh(QTreeWidgetItem *item)
{
    if (item)
    {
        while (item->childCount())
        {
            qDeleteAll(item->takeChildren());
        }
        QDir dir(item->data(0, RolePath).toString());
        if (dir.exists())
        {
            QFileInfoList files = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst);
            foreach (QFileInfo fi, files)
            {
                QTreeWidgetItem *child = new QTreeWidgetItem(item);
                child->setData(0, RoleType, QVariant::fromValue(fi.isDir() ? TypeDir : TypeFile));
                child->setData(0, RolePath, QVariant::fromValue(fi.absoluteFilePath()));
                child->setIcon(0, _fip.icon(fi));
                child->setText(0, fi.fileName());
                item->addChild(child);
                if (fi.isDir())
                {
                    onItemRefresh(child);
                }
            }
        }
    }
}

void ProjectDock::onProjectOpen(const QString &p)
{
    while (_tree->topLevelItemCount())
    {
        delete _tree->topLevelItem(0);
    }
    QFileInfo fi(p);
    QTreeWidgetItem *item = new QTreeWidgetItem(_tree);
    item->setData(0, RoleType, QVariant::fromValue(TypeDir));
    item->setData(0, RolePath, QVariant::fromValue(p));
    item->setIcon(0, _fip.icon(fi));
    item->setText(0, fi.fileName());
    onItemRefresh(item);
    _tree->addTopLevelItem(item);
    _tree->expandItem(item);
}

void ProjectDock::onProjectReload()
{
    onItemRefresh(_tree->topLevelItem(0));
}

ProjectDock::~ProjectDock()
{
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
