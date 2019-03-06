#ifndef APKDECOMPILEWORKER_H
#define APKDECOMPILEWORKER_H

#include <QObject>

class ApkDecompileWorker : public QObject
{
    Q_OBJECT
public:
    explicit ApkDecompileWorker(const QString &apk, const QString &folder, const bool sources, QObject *parent = nullptr);
    void decompile();
private:
    QString m_Apk;
    QString m_Folder;
    bool m_Sources;
signals:
    void decompileFailed(const QString &apk);
    void decompileFinished(const QString &apk, const QString &folder);
    void decompileProgress(const int percent, const QString &message);
};

#endif // APKDECOMPILEWORKER_H
