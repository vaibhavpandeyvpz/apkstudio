#include "include/updatedownloader.h"
#include "include/qrc.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

APP_NAMESPACE_START

UpdateDownloader::UpdateDownloader(QWidget *p)
    : Dialog(__("download_updates", "titles"), p), _state(NAM_IDLE)
{
    _connections << connect(&_nam, &QNetworkAccessManager::finished, this, &UpdateDownloader::onNetworkReply);
    _url = QString(URL_DOWNLOADS).arg(APP_VERSION);
    QNetworkRequest request;
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setUrl(QUrl(_url));
    _state = NAM_FETCHING;
    _nam.get(request);
}

void UpdateDownloader::onNetworkReply(QNetworkReply *reply)
{
    switch (_state)
    {
    case NAM_FETCHING:
    {
        QJsonDocument d = QJsonDocument::fromJson(reply->readAll());
        if (d.isObject())
        {
            QJsonObject json = d.object();
        }
        else
        {
            QMessageBox::critical(this, __("download_failed", "titles"), __("network_error_fetch", "messages", _url), QMessageBox::Close);
            reject();
        }
        break;
    }
    }
    _state = NAM_IDLE;
}

UpdateDownloader::~UpdateDownloader()
{
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
