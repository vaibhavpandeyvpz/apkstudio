#include "projects.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Projects::Projects(QStandardItemModel *model, QWidget *parent) :
    Dockable(translate("title_dock"), parent)
{
    tabs = new QTabWidget(this);
    tabs->setMinimumSize(64, 64);
    createProjectsTab(model);
    createProjectTab(model);
    setObjectName("projects");
    setWidget(tabs);
}

void Projects::createProjectTab(QStandardItemModel *model)
{
    QWidget *tab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(tab);
    current = new QComboBox(tab);
    current->setModel(model);
    current->setStyleSheet(STYLESHEET_COMBOBOXES);
    project = new QTreeView(tab);
    project->header()->hide();
    project->setContextMenuPolicy(Qt::CustomContextMenu);
    project->setEditTriggers(QAbstractItemView::NoEditTriggers);
    project->setModel(model);
    project->setSelectionBehavior(QAbstractItemView::SelectItems);
    project->setSelectionMode(QAbstractItemView::SingleSelection);
    project->setSortingEnabled(false);
    connections.append(connect(current, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [ this ] (int index) {
        if (index < 0) {
            this->tabs->setTabText(1, translate("tab_no_project"));
            return;
        }
        this->tabs->setTabText(1, translate("tab_active_project").arg(this->current->currentText()));
        this->project->setRootIndex(this->current->model()->index(index, 0));
    }));
    connections.append(connect(project, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onNodeClicked(QModelIndex))));
    layout->addWidget(current);
    layout->addWidget(project);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(1);
    tab->setLayout(layout);
    tabs->addTab(tab, translate("tab_no_project"));
}

void Projects::createProjectsTab(QStandardItemModel *model)
{
    QWidget *tab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(tab);
    projects = new QTreeView(this);
    projects->header()->hide();
    projects->setContextMenuPolicy(Qt::CustomContextMenu);
    projects->setEditTriggers(QAbstractItemView::NoEditTriggers);
    projects->setModel(model);
    projects->setSelectionBehavior(QAbstractItemView::SelectItems);
    projects->setSelectionMode(QAbstractItemView::SingleSelection);
    projects->setSortingEnabled(false);
    connections.append(connect(projects, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onNodeClicked(QModelIndex))));
    layout->addWidget(projects);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(1);
    tab->setLayout(layout);
    tabs->addTab(tab, translate("tab_projects"));
}

void Projects::onNodeClicked(const QModelIndex &index)
{
    if (!index.isValid() || index.data(ROLE_TYPE).value<int>() != TYPE_FILE)
        return;
    emit editFile(index.data(ROLE_PATH).value<QString>());
}

QModelIndex Projects::selected()
{
    return current->model()->index(current->currentIndex(), 0);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
