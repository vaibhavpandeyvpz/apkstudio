#include "cli.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

CLI::CLI(const QString &executable, QObject *parent) :
    QObject(parent), executable(executable)
{
}

QStringList CLI::execute(const QStringList &commands) const
{
    QStringList result;
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(executable, commands, QIODevice::ReadOnly);
    if (!process.waitForStarted())
        goto finish;
    if (!process.waitForFinished())
        process.kill();
    result = QString(process.readAll()).split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    finish:
    return result;
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
