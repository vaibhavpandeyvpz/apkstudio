#include "recents.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Recents::Recents(QObject *receiver, QWidget *parent) :
    QMenu(translate("item_recents"), parent)
{
    QList<QAction *> actions;
    QStringList recents = Settings::recentFiles();
    foreach (const QString &recent, recents) {
        QFileInfo file(recent);
        if (!file.exists())
            continue;
        QString path(file.absoluteDir().absolutePath());
        if (path.length() > 24)
            path.chop(path.length() - 24);
        path.append(".../").append(file.fileName());
        QAction *action = new QAction(path, this);
        connections.append(connect(action, &QAction::triggered, [ file, this ] () {
            emit recentSelected(file);
        }));
        actions << action;
    }
    if (actions.count() <= 0) {
        setEnabled(false);
        return;
    }
    addActions(actions);
    connections.append(connect(this, "2recentSelected(QFileInfo)", receiver, "1onActionRecentSelected(QFileInfo)"));
}

Recents::~Recents()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Widgets
} // namespace APKStudio
} // namespace VPZ
