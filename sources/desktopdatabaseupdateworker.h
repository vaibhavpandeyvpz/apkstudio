#ifndef DESKTOPDATABASEUPDATEWORKER_H
#define DESKTOPDATABASEUPDATEWORKER_H

#include <QObject>
#include <QString>

class DesktopDatabaseUpdateWorker : public QObject
{
    Q_OBJECT
public:
    explicit DesktopDatabaseUpdateWorker(const QString &applicationsDir, QObject *parent = nullptr);
    void updateDatabase();
signals:
    void finished();
    void error(const QString &message);
    void started();
private:
    QString m_ApplicationsDir;
};

#endif // DESKTOPDATABASEUPDATEWORKER_H

