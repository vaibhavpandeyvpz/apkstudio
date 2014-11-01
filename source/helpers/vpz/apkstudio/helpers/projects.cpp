#include "projects.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

Projects::Projects(QObject *parent) :
    QStandardItemModel(parent)
{
    directories << "res";
    files << "apk";
    files << "db";
    files << "java";
    files << "png";
    files << "smali";
    files << "txt";
    files << "wav";
    files << "xml";
    files << "yml";
}

bool Projects::close(const QModelIndex &selected)
{
    if (!selected.isValid())
        return false;
    QStandardItem *project = this->itemFromIndex(selected);
    while (project->rowCount())
        qDeleteAll(project->takeRow(0));
    return removeRow(selected.row(), index(0, 0));
}

bool Projects::open(const QFileInfo &yml)
{
    QDir directory = yml.dir();
    QStandardItem *node = new QStandardItem(::icon("project"), directory.dirName());
    node->setData(QVariant(directory.absolutePath()), ROLE_PATH);
    node->setData(QVariant(TYPE_PROJECT), ROLE_TYPE);
    appendRow(node);
    refresh(node);
    return true;
}

void Projects::refresh(QStandardItem *node)
{
    while (node->rowCount()) {
        QList<QStandardItem *> children = node->takeRow(0);
        qDeleteAll(children);
    }
    QDir directory(node->data(ROLE_PATH).value<QString>());
    QFileInfoList list = directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst);
    if (list.empty() || (list.count() < 1))
        return;
    foreach (const QFileInfo &info, list) {
        QStandardItem *child = new QStandardItem();
        if (info.isFile()) {
            child->setData(QVariant(TYPE_FILE), ROLE_TYPE);
            QString extension = info.suffix();
            if (files.contains(extension))
                child->setIcon(::icon(extension.toLatin1().data()));
            else
                child->setIcon(::icon("file"));
            child->setText(info.fileName());
        } else {
            child->setData(QVariant(TYPE_DIRECTORY), ROLE_TYPE);
            QString directory = info.baseName();
            if (directories.contains(directory))
                child->setIcon(::icon(directory.toLatin1().data()));
            else
                child->setIcon(::icon("directory"));
            child->setText(info.baseName());
        }
        child->setData(QVariant(info.absoluteFilePath()), ROLE_PATH);
        node->appendRow(child);
        if (info.isDir())
            refresh(child);
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
