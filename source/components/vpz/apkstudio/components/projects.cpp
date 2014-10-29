#include "projects.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Projects::Projects(QWidget *parent) :
    QDockWidget(translate("title_dock"), parent)
{
    tabs = new QTabWidget(this);
    tabs->setMinimumSize(64, 64);
    createProjectsTab();
    createProjectTab();
    setContentsMargins(2, 2, 2, 2);
    setObjectName("projects");
    setWidget(tabs);
}

void Projects::createProjectTab()
{
    QWidget *tab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(tab);
    current = new QComboBox(tab);
    project = new QTreeWidget(tab);
    project->header()->hide();
    project->setContextMenuPolicy(Qt::CustomContextMenu);
    project->setEditTriggers(QAbstractItemView::NoEditTriggers);
    project->setSelectionBehavior(QAbstractItemView::SelectItems);
    project->setSelectionMode(QAbstractItemView::SingleSelection);
    project->setSortingEnabled(false);
    layout->addWidget(current);
    layout->addWidget(project);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(1);
    tab->setLayout(layout);
    tabs->addTab(tab, translate("tab_active_project"));
}

void Projects::createProjectsTab()
{
    QWidget *tab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(tab);
    projects = new QTreeWidget(this);
    projects->header()->hide();
    projects->setContextMenuPolicy(Qt::CustomContextMenu);
    projects->setEditTriggers(QAbstractItemView::NoEditTriggers);
    projects->setSelectionBehavior(QAbstractItemView::SelectItems);
    projects->setSelectionMode(QAbstractItemView::SingleSelection);
    projects->setSortingEnabled(false);
    layout->addWidget(projects);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(1);
    tab->setLayout(layout);
    tabs->addTab(tab, translate("tab_projects"));
}

Projects::~Projects()
{
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
