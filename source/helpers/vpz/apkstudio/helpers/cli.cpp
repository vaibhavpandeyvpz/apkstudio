#include "cli.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

CLI::CLI(const QString &executable, QObject *parent) :
    QObject(parent), executable(executable)
{
}

QStringList CLI::execute(const QStringList &arguments) const
{
    QStringList result;
    QStringList output;
    QProcess process;
    process.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(executable, arguments, QIODevice::ReadOnly);
    if (!process.waitForStarted(30 * 1000))
        goto finish;
    process.waitForFinished(-1);
    output = QString(process.readAll()).split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    foreach (const QString &line, output)
        result.append(line.trimmed());
    finish:
    return result;
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
