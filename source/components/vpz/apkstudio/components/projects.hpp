#ifndef VPZ_APKSTUDIO_COMPONENTS_PROJECTS_HPP
#define VPZ_APKSTUDIO_COMPONENTS_PROJECTS_HPP

#include <QComboBox>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QTabWidget>
#include <QTreeView>
#include <QVBoxLayout>
#include "helpers/settings.hpp"
#include "helpers/text.hpp"
#include "dockable.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Projects : public Dockable
{
    Q_OBJECT
private:
    QComboBox *current;
    QTreeView *project;
    QTreeView *projects;
    QTabWidget *tabs;
private:
    static QString translate(const char *key) {
        return Helpers::Text::translate("projects", key);
    }
    void createProjectTab(QStandardItemModel *);
    void createProjectsTab(QStandardItemModel *);
private slots:
    void onNodeClicked(const QModelIndex &);
public:
    explicit Projects(QStandardItemModel *, QWidget * = 0);
    QModelIndex selected();
signals:
    void editFile(QString);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_PROJECTS_HPP
