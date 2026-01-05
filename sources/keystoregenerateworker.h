#ifndef KEYSTOREGENERATEWORKER_H
#define KEYSTOREGENERATEWORKER_H

#include <QObject>

class KeystoreGenerateWorker : public QObject
{
    Q_OBJECT
public:
    explicit KeystoreGenerateWorker(const QString &keystorePath,
                                    const QString &keystorePassword,
                                    const QString &alias,
                                    const QString &aliasPassword,
                                    int validity,
                                    const QString &keyAlgorithm,
                                    int keySize,
                                    QObject *parent = nullptr);
    void generate();
private:
    QString m_KeystorePath;
    QString m_KeystorePassword;
    QString m_Alias;
    QString m_AliasPassword;
    int m_Validity;
    QString m_KeyAlgorithm;
    int m_KeySize;
signals:
    void generateFailed(const QString &error);
    void generateFinished(const QString &keystorePath);
    void generateProgress(const int percent, const QString &message);
    void finished();
    void started();
};

#endif // KEYSTOREGENERATEWORKER_H


