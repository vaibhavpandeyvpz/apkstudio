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
    QProcess process;
    process.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(executable, arguments, QIODevice::ReadOnly);
    if (!process.waitForStarted(30 * 1000))
        goto finish;
    process.waitForFinished(-1);
    result = QString(process.readAll()).split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    finish:
    return result;
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
