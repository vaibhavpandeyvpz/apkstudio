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
    createProjectTab();
    createProjectsTab();
    setContentsMargins(2, 2, 2, 2);
    setObjectName("projects");
    setWidget(tabs);
}

void Projects::createProjectTab()
{
    tabs->addTab(new QWidget(this), translate("tab_projects"));
}

void Projects::createProjectsTab()
{
    tabs->addTab(new QWidget(this), translate("tab_active_project"));
}

Projects::~Projects()
{
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
