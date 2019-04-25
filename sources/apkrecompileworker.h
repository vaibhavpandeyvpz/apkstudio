#ifndef APKRECOMPILEWORKER_H
#define APKRECOMPILEWORKER_H

#include <QObject>

class ApkRecompileWorker : public QObject
{
    Q_OBJECT
public:
    explicit ApkRecompileWorker(const QString &folder, QObject *parent = nullptr);
    void recompile();
private:
    QString m_Folder;
signals:
    void finished();
    void recompileFailed(const QString &folder);
    void recompileFinished(const QString &folder);
    void started();
};

#endif // APKRECOMPILEWORKER_H
