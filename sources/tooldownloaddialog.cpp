#include <QApplication>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QPushButton>
#include <QThread>
#include <QTimer>
#include "tooldownloaddialog.h"
#include "tooldownloadworker.h"

ToolDownloadDialog::ToolDownloadDialog(const QList<ToolDownloadWorker::ToolType> &tools, QWidget *parent)
    : QDialog(parent), m_Tools(tools), m_CurrentToolIndex(0), m_Success(false), m_Cancelled(false), m_CurrentWorker(nullptr), m_CurrentThread(nullptr)
{
    setWindowTitle(tr("Downloading binaries"));
    setModal(true);
    setMinimumWidth(500);
    setMinimumHeight(200);
    
    auto layout = new QVBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(15, 15, 15, 15);
    
    m_ToolLabel = new QLabel("", this);
    m_ToolLabel->setWordWrap(true);
    QFont toolFont = m_ToolLabel->font();
    toolFont.setBold(true);
    toolFont.setPointSize(toolFont.pointSize() + 1);
    m_ToolLabel->setFont(toolFont);
    layout->addWidget(m_ToolLabel);
    
    m_StatusLabel = new QLabel("", this);
    m_StatusLabel->setWordWrap(true);
    layout->addWidget(m_StatusLabel);
    
    m_ProgressBar = new QProgressBar(this);
    m_ProgressBar->setRange(0, 100);
    m_ProgressBar->setValue(0);
    m_ProgressBar->setTextVisible(true);
    layout->addWidget(m_ProgressBar);
    
    m_DetailLabel = new QLabel("", this);
    m_DetailLabel->setWordWrap(true);
    m_DetailLabel->setStyleSheet("QLabel { color: gray; }");
    layout->addWidget(m_DetailLabel);
    
    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    m_CancelButton = new QPushButton(tr("Cancel"), this);
    connect(m_CancelButton, &QPushButton::clicked, this, &ToolDownloadDialog::handleCancel);
    buttonLayout->addWidget(m_CancelButton);
    layout->addLayout(buttonLayout);
    
    if (m_Tools.isEmpty()) {
        m_StatusLabel->setText(tr("No tools to download."));
        m_CancelButton->setText(tr("Close"));
        return;
    }
    
    // Start first download
    startNextDownload();
}

void ToolDownloadDialog::startNextDownload()
{
    if (m_Cancelled || m_CurrentToolIndex >= m_Tools.size()) {
        if (!m_Cancelled && m_Success) {
            m_StatusLabel->setText(tr("All tools downloaded successfully!"));
            m_DetailLabel->setText(tr("Downloaded %1 tool(s)").arg(m_DownloadedPaths.size()));
        }
        m_CancelButton->setText(tr("Close"));
        m_ProgressBar->setValue(100);
        return;
    }
    
    ToolDownloadWorker::ToolType tool = m_Tools[m_CurrentToolIndex];
    QString toolName = getToolName(tool);
    
    m_ToolLabel->setText(tr("%1 (%2 of %3)...")
                         .arg(toolName)
                         .arg(m_CurrentToolIndex + 1)
                         .arg(m_Tools.size()));
    m_StatusLabel->setText(tr("Preparing to download %1...").arg(toolName));
    m_ProgressBar->setValue(0);
    m_DetailLabel->setText("");
    
    // Start download in background thread
    m_CurrentThread = new QThread(this);
    m_CurrentWorker = new ToolDownloadWorker(tool, nullptr);
    m_CurrentWorker->moveToThread(m_CurrentThread);
    
    connect(m_CurrentThread, &QThread::started, m_CurrentWorker, &ToolDownloadWorker::download);
    connect(m_CurrentWorker, &ToolDownloadWorker::progress, this, &ToolDownloadDialog::handleProgress);
    connect(m_CurrentWorker, &ToolDownloadWorker::finished, this, &ToolDownloadDialog::handleFinished);
    connect(m_CurrentWorker, &ToolDownloadWorker::failed, this, &ToolDownloadDialog::handleFailed);
    connect(m_CurrentWorker, &ToolDownloadWorker::finished, m_CurrentThread, &QThread::quit);
    connect(m_CurrentWorker, &ToolDownloadWorker::failed, m_CurrentThread, &QThread::quit);
    connect(m_CurrentThread, &QThread::finished, m_CurrentWorker, &QObject::deleteLater);
    connect(m_CurrentThread, &QThread::finished, m_CurrentThread, &QObject::deleteLater);
    connect(m_CurrentThread, &QThread::finished, [this]() {
        m_CurrentWorker = nullptr;
        m_CurrentThread = nullptr;
    });
    
    m_CurrentThread->start();
}

void ToolDownloadDialog::handleProgress(int percentage, const QString &message)
{
    if (m_Cancelled) return;
    
    // Calculate overall progress across all tools
    int toolProgress = (m_CurrentToolIndex * 100) + percentage;
    int overallProgress = toolProgress / m_Tools.size();
    m_ProgressBar->setValue(overallProgress);
    m_StatusLabel->setText(message);
    m_DetailLabel->setText(tr("Overall progress: %1% (%2 of %3 tools)")
                          .arg(overallProgress)
                          .arg(m_CurrentToolIndex + 1)
                          .arg(m_Tools.size()));
}

void ToolDownloadDialog::handleFinished(const QString &path)
{
    if (m_Cancelled) return;
    
    m_DownloadedPaths.append(path);
    m_CurrentToolIndex++;
    
    if (m_CurrentToolIndex < m_Tools.size()) {
        // Start next download
        QTimer::singleShot(500, this, &ToolDownloadDialog::startNextDownload);
    } else {
        // All downloads complete
        m_Success = true;
        m_ProgressBar->setValue(100);
        m_StatusLabel->setText(tr("All tools downloaded and installed successfully!"));
        m_DetailLabel->setText(tr("Downloaded %1 tool(s)").arg(m_DownloadedPaths.size()));
        m_ToolLabel->setText("");
        m_CancelButton->setText(tr("Close"));
    }
}

void ToolDownloadDialog::handleFailed(const QString &error)
{
    if (m_Cancelled) return;
    
    QString toolName = getToolName(m_Tools[m_CurrentToolIndex]);
    m_StatusLabel->setText(tr("Failed to download %1: %2").arg(toolName, error));
    m_DetailLabel->setText(tr("Please download %1 manually from the settings page.").arg(toolName));
    m_ProgressBar->setValue(0);
    m_CancelButton->setText(tr("Close"));
    m_Success = false;
}

void ToolDownloadDialog::closeEvent(QCloseEvent *event)
{
    // If all downloads are complete and successful, allow closing
    if (m_CurrentToolIndex >= m_Tools.size() && m_Success && !m_Cancelled) {
        event->accept();
        return;
    }
    
    // Cancel download if still in progress
    if (!m_Cancelled && m_CurrentWorker) {
        handleCancel();
    }
    event->accept();
}

void ToolDownloadDialog::handleCancel()
{
    // If all downloads are complete and successful, just close the dialog
    if (m_CurrentToolIndex >= m_Tools.size() && m_Success && !m_Cancelled) {
        accept();
        return;
    }
    
    if (m_Cancelled) {
        reject();
        return;
    }
    
    m_Cancelled = true;
    m_Success = false;
    
    if (m_CurrentWorker && m_CurrentThread) {
        // Abort the download first
        m_CurrentWorker->abort();
        
        // Disconnect signals from worker to prevent callbacks after cancellation
        disconnect(m_CurrentWorker, &ToolDownloadWorker::progress, this, nullptr);
        disconnect(m_CurrentWorker, &ToolDownloadWorker::finished, this, nullptr);
        disconnect(m_CurrentWorker, &ToolDownloadWorker::failed, this, nullptr);
        disconnect(m_CurrentWorker, &ToolDownloadWorker::finished, m_CurrentThread, nullptr);
        disconnect(m_CurrentWorker, &ToolDownloadWorker::failed, m_CurrentThread, nullptr);
        
        // Disconnect thread signals
        disconnect(m_CurrentThread, &QThread::started, m_CurrentWorker, nullptr);
        disconnect(m_CurrentThread, &QThread::finished, m_CurrentWorker, nullptr);
        disconnect(m_CurrentThread, &QThread::finished, m_CurrentThread, nullptr);
        disconnect(m_CurrentThread, &QThread::finished, this, nullptr);
        
        // Stop current download thread
        m_CurrentThread->quit();
        if (!m_CurrentThread->wait(1000)) {
            // Force termination if thread doesn't respond
            m_CurrentThread->terminate();
            m_CurrentThread->wait(500);
        }
        
        // Clean up - use deleteLater to ensure proper cleanup order
        if (m_CurrentWorker) {
            m_CurrentWorker->deleteLater();
            m_CurrentWorker = nullptr;
        }
        if (m_CurrentThread) {
            m_CurrentThread->deleteLater();
            m_CurrentThread = nullptr;
        }
    }
    
    m_StatusLabel->setText(tr("Download cancelled."));
    m_DetailLabel->setText(tr("Some tools may not be installed. Please download them manually from settings."));
    m_CancelButton->setText(tr("Close"));
}

QString ToolDownloadDialog::getToolName(ToolDownloadWorker::ToolType tool) const
{
    switch (tool) {
    case ToolDownloadWorker::Java:
        return tr("Java");
    case ToolDownloadWorker::Apktool:
        return tr("Apktool");
    case ToolDownloadWorker::Jadx:
        return tr("JADX");
    case ToolDownloadWorker::Adb:
        return tr("ADB");
    case ToolDownloadWorker::UberApkSigner:
        return tr("Uber APK Signer");
    }
    return tr("Tool");
}
