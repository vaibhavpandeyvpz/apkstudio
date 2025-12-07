#include <QDebug>
#include <QObject>
#include <QProcess>
#include "desktopdatabaseupdateworker.h"

DesktopDatabaseUpdateWorker::DesktopDatabaseUpdateWorker(const QString &applicationsDir, QObject *parent)
    : QObject(parent), m_ApplicationsDir(applicationsDir)
{
}

void DesktopDatabaseUpdateWorker::updateDatabase()
{
    emit started();
    
    // Check if update-desktop-database exists
    QProcess checkProcess;
    checkProcess.start("which", QStringList() << "update-desktop-database");
    if (!checkProcess.waitForFinished(1000)) {
        // Command doesn't exist or timed out, just finish silently
        emit finished();
        return;
    }
    
    if (checkProcess.exitCode() != 0) {
        // update-desktop-database not found, finish silently
        emit finished();
        return;
    }
    
    // Run update-desktop-database
    QProcess updateProcess;
    updateProcess.start("update-desktop-database", QStringList() << m_ApplicationsDir);
    
    if (!updateProcess.waitForFinished(10000)) { // Wait max 10 seconds
        emit error(QObject::tr("Desktop database update timed out"));
        emit finished();
        return;
    }
    
    if (updateProcess.exitCode() != 0) {
        QString errorOutput = QString::fromUtf8(updateProcess.readAllStandardError());
        emit error(QObject::tr("Desktop database update failed: %1").arg(errorOutput));
    }
    
    emit finished();
}

