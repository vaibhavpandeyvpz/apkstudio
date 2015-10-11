#include <QIcon>
#include "include/qrc.h"
#include "include/updatevendorbinaries.h"

APP_NAMESPACE_START

UpdateVendorBinaries::UpdateVendorBinaries(QWidget *p)
    : Dialog(__("update", "titles"), p)
{
    setWindowIcon(Qrc::icon("dialog_update"));
}

APP_NAMESPACE_END
