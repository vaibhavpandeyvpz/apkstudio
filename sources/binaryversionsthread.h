#ifndef BINARYVERSIONSTHREAD_H
#define BINARYVERSIONSTHREAD_H

#include <QThread>

class BinaryVersionsThread : public QThread
{
    Q_OBJECT
public:
    explicit BinaryVersionsThread(QObject *parent = nullptr);
    void run() override;
signals:
    void versionResolved(const QString &binary, const QString &version);
};

#endif // BINARYVERSIONSTHREAD_H
