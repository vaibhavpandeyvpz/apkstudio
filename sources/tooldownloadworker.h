#ifndef TOOLDOWNLOADWORKER_H
#define TOOLDOWNLOADWORKER_H

#include <QObject>
#include <QString>

class QNetworkAccessManager;
class QNetworkReply;
class QFile;

class ToolDownloadWorker : public QObject
{
    Q_OBJECT
public:
    enum ToolType {
        Java,
        Apktool,
        Jadx,
        Adb,
        UberApkSigner
    };
    Q_ENUM(ToolType)

    explicit ToolDownloadWorker(ToolType tool, QObject *parent = nullptr);
    ~ToolDownloadWorker();
    void download();
    void abort();

signals:
    void progress(int percentage, const QString &message);
    void finished(const QString &path);
    void failed(const QString &error);
    void started();

private:
    ToolType m_Tool;
    QNetworkAccessManager *m_NetworkManager;
    QNetworkReply *m_NetworkReply;
    QFile *m_DownloadFile;
    QString getDownloadUrl();
    QString getExtractPath();
    QString findExecutableInExtracted(const QString &extractedPath);
    QString findExecutableInSystemLocations();
    bool extractZip(const QString &zipPath, const QString &extractPath);
    bool extractTarGz(const QString &tarPath, const QString &extractPath);
    bool installPkg(const QString &pkgPath, const QString &installPath);
    bool installMsi(const QString &msiPath, const QString &installPath);
    void setExecutablePermissions(const QString &path);
    QString getLatestGitHubRelease(const QString &repo, const QString &assetPattern);
};

#endif // TOOLDOWNLOADWORKER_H


