#include "deviceinformation.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Components {

DeviceInformation::DeviceInformation(QWidget *parent) :
    QGridLayout(parent)
{
    QGroupBox *ghardware = new QGroupBox(translate("group_hardware"), parent);
    QGroupBox *gnetwork = new QGroupBox(translate("group_network"), parent);
    QGroupBox *gsoftware = new QGroupBox(translate("group_software"), parent);
    QFormLayout *lhardware = new QFormLayout(ghardware);
    QFormLayout *lnetwork = new QFormLayout(gnetwork);
    QFormLayout *lsoftware = new QFormLayout(gsoftware);
    QLineEdit *board = new QLineEdit(ghardware);
    QLineEdit *cpu = new QLineEdit(ghardware);
    QLineEdit *imei = new QLineEdit(ghardware);
    QLineEdit *manufacturer = new QLineEdit(ghardware);
    QLineEdit *model = new QLineEdit(ghardware);
    QLineEdit *secure = new QLineEdit(ghardware);
    QLineEdit *country = new QLineEdit(gnetwork);
    QLineEdit *operator_ = new QLineEdit(gnetwork);
    QLineEdit *timezone = new QLineEdit(gnetwork);
    QLineEdit *type = new QLineEdit(gnetwork);
    QLineEdit *build = new QLineEdit(gsoftware);
    QLineEdit *date = new QLineEdit(gsoftware);
    QLineEdit *fingerprint = new QLineEdit(gsoftware);
    QLineEdit *sdk = new QLineEdit(gsoftware);
    QLineEdit *tags = new QLineEdit(gsoftware);
    QLineEdit *version = new QLineEdit(gsoftware);
    board->setReadOnly(true);
    cpu->setReadOnly(true);
    imei->setReadOnly(true);
    manufacturer->setReadOnly(true);
    model->setReadOnly(true);
    secure->setReadOnly(true);
    country->setReadOnly(true);
    operator_->setReadOnly(true);
    timezone->setReadOnly(true);
    type->setReadOnly(true);
    build->setReadOnly(true);
    date->setReadOnly(true);
    fingerprint->setReadOnly(true);
    sdk->setReadOnly(true);
    tags->setReadOnly(true);
    version->setReadOnly(true);
    addWidget(ghardware, 0, 0);
    addWidget(gnetwork, 0, 1);
    addWidget(gsoftware, 1, 0, 1, 2);
    lhardware->addRow(translate("label_manufacturer"), manufacturer);
    lhardware->addRow(translate("label_model"), model);
    lhardware->addRow(translate("label_imei"), imei);
    lhardware->addRow(translate("label_board"), board);
    lhardware->addRow(translate("label_cpu"), cpu);
    lhardware->addRow(translate("label_secure"), secure);
    lnetwork->addRow(translate("label_type"), type);
    lnetwork->addRow(translate("label_country"), country);
    lnetwork->addRow(translate("label_operator"), operator_);
    lnetwork->addRow(translate("label_timezone"), timezone);
    lsoftware->addRow(translate("label_version"), version);
    lsoftware->addRow(translate("label_sdk"), sdk);
    lsoftware->addRow(translate("label_build"), build);
    lsoftware->addRow(translate("label_fingerprint"), fingerprint);
    lsoftware->addRow(translate("label_date"), date);
    lsoftware->addRow(translate("label_tags"), tags);
    ghardware->setLayout(lhardware);
    gnetwork->setLayout(lnetwork);
    gsoftware->setLayout(lsoftware);
    connections.append(connect(this, &DeviceInformation::updateIMEI, [ imei ] (const QString &number) {
        imei->setText(number);
    }));
    connections.append(connect(this, &DeviceInformation::updateInformation, [ board, cpu, manufacturer, model, secure, country, operator_, timezone, type, build, date, fingerprint, sdk, tags, version ] (const QMap<QString, QString> &information) {
        board->setText(information.value(QString("ro.product.board")));
        cpu->setText(information.value(QString("ro.product.cpu.abi")));
        manufacturer->setText(Text::capitalize(information.value(QString("ro.product.manufacturer"))));
        model->setText(information.value(QString("ro.product.model")));
        secure->setText(information.value(QString("ro.secure")));
        country->setText(information.value(QString("gsm.sim.operator.iso-country")).toUpper());
        operator_->setText(Text::capitalize(information.value(QString("gsm.sim.operator.alpha")), true));
        timezone->setText(information.value(QString("persist.sys.timezone")));
        type->setText(information.value(QString("gsm.network.type")));
        build->setText(information.value(QString("ro.build.description")));
        date->setText(Format::timestamp(QDateTime::fromTime_t(information.value(QString("ro.build.date.utc")).toInt())));
        fingerprint->setText(information.value(QString("ro.build.fingerprint")));
        sdk->setText(information.value(QString("ro.build.version.sdk")));
        tags->setText(information.value(QString("ro.build.tags")));
        version->setText(information.value(QString("ro.build.version.release")));
    }));
}

void DeviceInformation::setDevice(const QString &serial)
{
    emit updateIMEI(ADB::instance()->imei(serial));
    emit updateInformation(ADB::instance()->properties(serial));
}

DeviceInformation::~DeviceInformation()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Components
} // namespace APKStudio
} // namespace VPZ
