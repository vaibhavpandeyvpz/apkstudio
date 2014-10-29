#include "cli.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

CLI::CLI(const QString &binary, QObject *parent) :
    QObject(parent), binary(binary)
{
}

QStringList CLI::execute(const QStringList &arguments, const QString &binary) const
{
    QStringList result;
    QStringList output;
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
    process.start((binary.isEmpty() ? this->binary : binary), arguments, QIODevice::ReadOnly);
    if (!process.waitForStarted(30 * 1000))
        goto finish;
    process.waitForFinished(-1);
    output = QString(process.readAll()).split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    foreach (const QString &line, output)
        result.append(line.trimmed());
    finish:
    emit commandExecuted(arguments, output);
    return result;
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
