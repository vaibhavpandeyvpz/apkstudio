#ifndef UPDATEDOWNLOADER_H
#define UPDATEDOWNLOADER_H

#include <QNetworkReply>
#include "dialog.h"
#include "macros.h"

APP_NAMESPACE_START

class UpdateDownloader : public Dialog
{
    Q_OBJECT
private:
    enum NamState {
        NAM_IDLE = 0,
        NAM_FETCHING,
        NAM_DOWNLOADING
    };
private:
    APP_CONNECTIONS_LIST
    QNetworkAccessManager _nam;
    int _state;
    QString _url;
private slots:
    void onNetworkReply(QNetworkReply *reply);
public:
    explicit UpdateDownloader(QWidget *parent);
    ~UpdateDownloader();
};

APP_NAMESPACE_END

#endif // UPDATEDOWNLOADER_H
