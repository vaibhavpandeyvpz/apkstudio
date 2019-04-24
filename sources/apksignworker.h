#ifndef APKSIGNWORKER_H
#define APKSIGNWORKER_H

#include <QObject>

class ApkSignWorker : public QObject
{
    Q_OBJECT
public:
    explicit ApkSignWorker(const QString &apk, const QString &keystore = QString(), const QString &keystorePassword = QString(), const QString &alias = QString(), const QString &aliasPassword = QString(), const bool zipalign = true, QObject *parent = nullptr);
    void sign();
private:
    QString m_Apk;
    QString m_Keystore;
    QString m_KeystorePassword;
    QString m_Alias;
    QString m_AliasPassword;
    bool m_Zipalign;
signals:
    void signFailed(const QString &apk);
    void signFinished(const QString &apk);
};

#endif // APKSIGNWORKER_H
