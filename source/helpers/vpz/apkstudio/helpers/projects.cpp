#include "projects.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

Projects::Projects(QWidget *parent) :
    QStandardItemModel(parent)
{
    directories << "res";
    files << "apk";
    files << "java";
    files << "png";
    files << "smali";
    files << "xml";
    watcher = new QFileSystemWatcher(this);
    connections.append(connect(watcher, static_cast<void(QFileSystemWatcher::*)(QString)>(QFileSystemWatcher::directoryChanged), this, &Projects::onDirectoryChanged));
    connections.append(connect(watcher, static_cast<void(QFileSystemWatcher::*)(QString)>(QFileSystemWatcher::fileChanged), this, &Projects::onFileChanged));
}

bool Projects::close(const QFileInfo &yml)
{
}

bool Projects::onDirectoryChanged(const QString &path)
{
}

bool Projects::onFileChanged(const QString &path)
{
}

bool Projects::open(const QFileInfo &yml)
{
    if (!yml.exists() || root.isFile() || (root.suffix() != "yml"))
        return;
    QDir directory = yml.dir();
    QStandardItem *node = new QStandardItem(icon("project"), directory.dirName());
    node->setData(QVariant(directory.absolutePath()), ROLE_PATH);
    node->setData(QVariant(TYPE_PROJECT), ROLE_TYPE);
    appendRow(node);
    watcher->addPath(directory.absolutePath());
    refresh(node);
}

bool Projects::refresh(QStandardItem *node)
{
    while (node->rowCount()) {
        QList<QStandardItem* > children = node->takeRow(0);
        qDeleteAll(children);
    }
    QString path = qvariant_cast<QString>(node->data(ROLE_PATH));
    if (path.isNull() || path.isEmpty())
        return;
    QDir directory(path);
    if (!directory.exists())
        return;
    QFileInfoList list = directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst);
    if (list.empty() || (list.count() < 1))
        return;
    foreach (const QFileInfo &info, list) {
        QStandardItem *child = new QStandardItem();
        if (info.isFile()) {
            child->setData(QVariant(TYPE_FILE), ROLE_TYPE);
            QString extension = info.suffix();
            if (files.contains(extension))
                child->setIcon(icon(extension));
            else
                child->setIcon(icon("file"));
            child->setText(info.fileName());
        } else {
            child->setData(QVariant(TYPE_DIRECTORY), ROLE_TYPE);
            QString directory = info.baseName();
            if (directories.contains(directory))
                child->setIcon(icon(directory));
            else
                child->setIcon(icon("directory"));
            child->setText(info.baseName());
            watcher->addPath(info.absolutePath());
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
