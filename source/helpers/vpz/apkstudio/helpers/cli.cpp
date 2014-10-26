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
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    if (environment.contains("JAVA_HOME")) {
        QString java = QString(environment.value("JAVA_HOME")).append("\\bin");
        QStringList path = environment.value("PATH").split(';');
        if (!path.contains(java))
            path.append(java);
        environment.insert("PATH", path.join(';'));
    }
    QStringList result;
    QStringList output;
    QProcess process;
    process.setEnvironment(environment.toStringList());
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start((binary.isEmpty() ? this->binary : binary), arguments, QIODevice::ReadOnly);
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
