#ifndef VERSIONRESOLVEWORKER_H
#define VERSIONRESOLVEWORKER_H

#include <QObject>

class VersionResolveWorker : public QObject
{
    Q_OBJECT
public:
    explicit VersionResolveWorker(QObject *parent = nullptr);
    void resolve();
signals:
    void finished();
    void started();
    void versionResolved(const QString &binary, const QString &version);
};

#endif // VERSIONRESOLVEWORKER_H
