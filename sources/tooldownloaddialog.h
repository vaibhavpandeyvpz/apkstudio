#ifndef TOOLDOWNLOADDIALOG_H
#define TOOLDOWNLOADDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QList>
#include "tooldownloadworker.h"

class ToolDownloadDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ToolDownloadDialog(const QList<ToolDownloadWorker::ToolType> &tools, QWidget *parent = nullptr);
    QList<QString> downloadedPaths() const { return m_DownloadedPaths; }
    bool wasSuccessful() const { return m_Success; }

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void handleProgress(int percentage, const QString &message);
    void handleFinished(const QString &path);
    void handleFailed(const QString &error);
    void handleCancel();

private:
    void startNextDownload();
    QString getToolName(ToolDownloadWorker::ToolType tool) const;
    
    QList<ToolDownloadWorker::ToolType> m_Tools;
    int m_CurrentToolIndex;
    QProgressBar *m_ProgressBar;
    QLabel *m_StatusLabel;
    QLabel *m_DetailLabel;
    QLabel *m_ToolLabel;
    QPushButton *m_CancelButton;
    QList<QString> m_DownloadedPaths;
    bool m_Success;
    bool m_Cancelled;
    ToolDownloadWorker *m_CurrentWorker;
    QThread *m_CurrentThread;
};

#endif // TOOLDOWNLOADDIALOG_H
