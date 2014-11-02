#include "projects.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

Projects::Projects(QObject *parent) :
    QStandardItemModel(parent), editables(Settings::fileIcons()), directories(Settings::directoryIcons())
{
}

bool Projects::close(const QModelIndex &selected)
{
    if (!selected.isValid())
        return false;
    QStandardItem *project = itemFromIndex(selected);
    while (project->rowCount())
        qDeleteAll(project->takeRow(0));
    return removeRow(selected.row(), invisibleRootItem()->index());
}

bool Projects::open(const QFileInfo &yml)
{
    QDir directory = yml.dir();
    QStandardItem *node = new QStandardItem(::icon("project"), directory.dirName());
    node->setData(QVariant(directory.absolutePath()), ROLE_PATH);
    node->setData(QVariant(TYPE_PROJECT), ROLE_TYPE);
    appendRow(node);
    traverse(node);
    return true;
}

void Projects::traverse(QStandardItem *node)
{
    while (node->rowCount()) {
        QList<QStandardItem *> children = node->takeRow(0);
        qDeleteAll(children);
    }
    QDir directory(node->data(ROLE_PATH).value<QString>());
    directory.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks);
    QFileInfoList files = directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst);
    foreach (const QFileInfo &file, files) {
        if (file.fileName().startsWith('.'))
            continue;
        QStandardItem *child = new QStandardItem();
        if (file.isFile()) {
            child->setData(QVariant(TYPE_FILE), ROLE_TYPE);
            if (editables.contains(file.suffix()))
                child->setIcon(::icon(file.suffix()));
            else
                child->setIcon(::icon("file"));
            child->setText(file.fileName());
        } else {
            child->setData(QVariant(TYPE_DIRECTORY), ROLE_TYPE);
            QString directory = file.baseName();
            if (directories.contains(directory))
                child->setIcon(::icon(directory));
            else
                child->setIcon(::icon("directory"));
            child->setText(file.baseName());
        }
        child->setData(QVariant(file.absoluteFilePath()), ROLE_PATH);
        node->appendRow(child);
        if (file.isDir())
            traverse(child);
    }
}

Projects::~Projects()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
