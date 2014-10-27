#include "information.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

Information::Information(QWidget *parent) :
    QTabWidget(parent)
{
    inflateHardware();
    inflateSoftware();
    inflateNetwork();
    setMinimumSize(160, 160);
}

void Information::inflateHardware()
{
    QWidget *tab = new QWidget(this);
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
        board->setText(information.value(QString("ro.product.board")));
        cpu->setText(information.value(QString("ro.product.cpu.abi")));
        manufacturer->setText(Text::capitalize(information.value(QString("ro.product.manufacturer"))));
        model->setText(information.value(QString("ro.product.model")));
        secure->setText(information.value(QString("ro.secure")));
    }));
    tab->setLayout(layout);
    addTab(tab, translate("tab_hardware"));
}

void Information::inflateNetwork()
{
    QWidget *tab = new QWidget(this);
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
        country->setText(information.value(QString("gsm.sim.operator.iso-country")).toUpper());
        operator_->setText(Text::capitalize(information.value(QString("gsm.sim.operator.alpha")), true));
        timezone->setText(information.value(QString("persist.sys.timezone")));
        type->setText(information.value(QString("gsm.network.type")));
    }));
    tab->setLayout(layout);
    addTab(tab, translate("tab_network"));
}

void Information::inflateSoftware()
{
    QWidget *tab = new QWidget(this);
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
        build->setText(information.value(QString("ro.build.description")));
        date->setText(Format::timestamp(QDateTime::fromTime_t(information.value(QString("ro.build.date.utc")).toInt())));
        fingerprint->setText(information.value(QString("ro.build.fingerprint")));
        mod->setText(information.value(QString("ro.modversion")));
        sdk->setText(information.value(QString("ro.build.version.sdk")));
        tags->setText(information.value(QString("ro.build.tags")));
        version->setText(information.value(QString("ro.build.version.release")));
    }));
    tab->setLayout(layout);
    addTab(tab, translate("tab_software"));
}

void Information::setDevice(const QString &serial)
{
    emit updateIMEI(ADB::instance()->imei(serial));
    emit updateInformation(ADB::instance()->properties(serial));
}

Information::~Information()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
