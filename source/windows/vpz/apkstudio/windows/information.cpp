#include "information.hpp"

using namespace VPZ::APKStudio::Helpers;
using namespace VPZ::APKStudio::Resources;

namespace VPZ {
namespace APKStudio {
namespace Windows {

Information::Information(const QString &device, QWidget *parent) :
    Dialog(parent), device(device)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    tabs = new QTabWidget(this);
    layout->addWidget(tabs);
    layout->setContentsMargins(2, 2, 2, 2);
    layout->setSpacing(0);
    createHardwareTab();
    createSoftwareTab();
    createNetworkTab();
    setLayout(layout);
    setWindowIcon(::icon("processor"));
    setWindowTitle(translate("title_window").arg(device));
}

void Information::createHardwareTab()
{
    QWidget *tab = new QWidget(tabs);
    QFormLayout *layout = new QFormLayout(tab);
    QLineEdit *board = new QLineEdit(tab);
    QLineEdit *cpu = new QLineEdit(tab);
    QLineEdit *imei = new QLineEdit(tab);
    QLineEdit *manufacturer = new QLineEdit(tab);
    QLineEdit *model = new QLineEdit(tab);
    QLineEdit *secure = new QLineEdit(tab);
    board->setReadOnly(true);
    cpu->setReadOnly(true);
    imei->setReadOnly(true);
    manufacturer->setReadOnly(true);
    model->setReadOnly(true);
    secure->setReadOnly(true);
    layout->addRow(translate("label_manufacturer"), manufacturer);
    layout->addRow(translate("label_model"), model);
    layout->addRow(translate("label_imei"), imei);
    layout->addRow(translate("label_board"), board);
    layout->addRow(translate("label_cpu"), cpu);
    layout->addRow(translate("label_secure"), secure);
    connections.append(connect(this, &Information::updateIMEI, [ imei ] (const QString &number) {
        imei->setText(number);
    }));
    connections.append(connect(this, &Information::updateInformation, [ board, cpu, manufacturer, model, secure ] (const QMap<QString, QString> &information) {
        board->setText(information.value("ro.product.board"));
        cpu->setText(information.value("ro.product.cpu.abi"));
        manufacturer->setText(Text::capitalize(information.value("ro.product.manufacturer")));
        model->setText(information.value("ro.product.model"));
        secure->setText(information.value("ro.secure"));
    }));
    tab->setLayout(layout);
    tabs->addTab(tab, translate("tab_hardware"));
}

void Information::createNetworkTab()
{
    QWidget *tab = new QWidget(tabs);
    QFormLayout *layout = new QFormLayout(tab);
    QLineEdit *country = new QLineEdit(tab);
    QLineEdit *operator_ = new QLineEdit(tab);
    QLineEdit *timezone = new QLineEdit(tab);
    QLineEdit *type = new QLineEdit(tab);
    country->setReadOnly(true);
    operator_->setReadOnly(true);
    timezone->setReadOnly(true);
    type->setReadOnly(true);
    layout->addRow(translate("label_country"), country);
    layout->addRow(translate("label_operator"), operator_);
    layout->addRow(translate("label_timezone"), timezone);
    layout->addRow(translate("label_type"), type);
    connections.append(connect(this, &Information::updateInformation, [ country, operator_, timezone, type ] (const QMap<QString, QString> &information) {
        country->setText(information.value("gsm.sim.operator.iso-country").toUpper());
        operator_->setText(Text::capitalize(information.value("gsm.sim.operator.alpha"), true));
        timezone->setText(information.value("persist.sys.timezone"));
        type->setText(information.value("gsm.network.type"));
    }));
    tab->setLayout(layout);
    tabs->addTab(tab, translate("tab_network"));
}

void Information::createSoftwareTab()
{
    QWidget *tab = new QWidget(tabs);
    QFormLayout *layout = new QFormLayout(tab);
    QLineEdit *build = new QLineEdit(tab);
    QLineEdit *date = new QLineEdit(tab);
    QLineEdit *fingerprint = new QLineEdit(tab);
    QLineEdit *mod = new QLineEdit(tab);
    QLineEdit *sdk = new QLineEdit(tab);
    QLineEdit *tags = new QLineEdit(tab);
    QLineEdit *version = new QLineEdit(tab);
    build->setReadOnly(true);
    date->setReadOnly(true);
    fingerprint->setReadOnly(true);
    mod->setReadOnly(true);
    sdk->setReadOnly(true);
    tags->setReadOnly(true);
    version->setReadOnly(true);
    layout->addRow(translate("label_version"), version);
    layout->addRow(translate("label_mod"), mod);
    layout->addRow(translate("label_sdk"), sdk);
    layout->addRow(translate("label_build"), build);
    layout->addRow(translate("label_fingerprint"), fingerprint);
    layout->addRow(translate("label_date"), date);
    layout->addRow(translate("label_tags"), tags);
    connections.append(connect(this, &Information::updateInformation, [ build, date, fingerprint, mod, sdk, tags, version ] (const QMap<QString, QString> &information) {
        build->setText(information.value("ro.build.description"));
        date->setText(Format::timestamp(QDateTime::fromTime_t(information.value("ro.build.date.utc").toInt())));
        fingerprint->setText(information.value("ro.build.fingerprint"));
        mod->setText(information.value("ro.modversion"));
        sdk->setText(information.value("ro.build.version.sdk"));
        tags->setText(information.value("ro.build.tags"));
        version->setText(information.value("ro.build.version.release"));
    }));
    tab->setLayout(layout);
    tabs->addTab(tab, translate("tab_software"));
}

void Information::onInitComplete()
{
    emit updateIMEI(ADB::instance()->IMEI(device));
    emit updateInformation(ADB::instance()->properties(device));
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ
