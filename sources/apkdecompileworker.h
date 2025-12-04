#ifndef APKDECOMPILEWORKER_H
#define APKDECOMPILEWORKER_H

#include <QObject>

class ApkDecompileWorker : public QObject
{
    Q_OBJECT
public:
    explicit ApkDecompileWorker(const QString &apk, const QString &folder, const bool smali, const bool resources, const bool java, const QString &frameworkTag = QString(), const QString &extraArguments = QString(), QObject *parent = nullptr);
    void decompile();
private:
    QString m_Apk;
    QString m_Folder;
    bool m_Java;
    bool m_Resources;
    bool m_Smali;
    QString m_FrameworkTag;
    QString m_ExtraArguments;
signals:
    void decompileFailed(const QString &apk);
    void decompileFinished(const QString &apk, const QString &folder);
    void decompileProgress(const int percent, const QString &message);
    void finished();
    void started();
};

#endif // APKDECOMPILEWORKER_H
