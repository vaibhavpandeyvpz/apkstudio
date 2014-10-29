#include "realtime.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

Realtime::Realtime(const QString &binary, QObject *parent) :
    QThread(parent), binary(binary), finished(false)
{
}

void Realtime::run()
{
    QProcess *process = new QProcess();
    process->setEnvironment(QProcess::systemEnvironment());
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->start(binary, arguments, QIODevice::ReadOnly);
    if (!process->waitForStarted()) {
        delete process;
        emit stateChanged(false);
        return;
    }
    emit stateChanged(true);
    connections.append(connect(process, &QProcess::readyReadStandardOutput, [ this, process ] () {
        QTextStream stream(process);
        QString line;
        do {
            line = stream.readLine();
            emit lineRead(line);
        } while (!this->finished && !line.isNull());
    }));
    if (!process->waitForReadyRead()) {
        process->kill();
        process->waitForFinished(-1);
        emit stateChanged(false);
        delete process;
        return;
    }
    while (true) {
        mutex.lock();
        if (finished)
            break;
        mutex.unlock();
        process->waitForFinished(100);
    }
    process->kill();
    process->waitForFinished(-1);
    emit stateChanged(false);
    delete process;
}

void Realtime::start(const QStringList &arguments)
{
    this->arguments = arguments;
    QThread::start();
}

void Realtime::stop()
{
    mutex.lock();
    finished = true;
    mutex.unlock();
}

Realtime::~Realtime()
{
    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
