#include "syncnetworkaccessmanager.h"
#include <QMessageBox>

SyncNetworAccesskManager::SyncNetworAccesskManager(QObject *parent) : QNetworkAccessManager(parent)
{

}

static bool isHandledByCaller(QNetworkReply* reply)
{
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return status == 401 || status == 403 || status == 404 || status == 409 || status == 429;
}

static void handleReplyError(QNetworkReply* reply)
{
    if (isHandledByCaller(reply))
        return;

    qDebug() << "Error code:" << reply->error();
    QString err = reply->errorString();
    QMessageBox::critical(nullptr, "Error", err);
}

QNetworkReply* SyncNetworAccesskManager::post(const QNetworkRequest &request, const QByteArray &data)
{
    QNetworkReply* reply = QNetworkAccessManager::post(request, data);

    connect(reply, &QNetworkReply::errorOccurred, this, [=]
    {
        handleReplyError(reply);
    });

    while (!reply->isFinished())
        QApplication::processEvents();

    return reply;
}

QNetworkReply* SyncNetworAccesskManager::get(const QNetworkRequest &request)
{
    QNetworkReply* reply = QNetworkAccessManager::get(request);

    connect(reply, &QNetworkReply::errorOccurred, this, [=]
    {
        handleReplyError(reply);
    });

    while (!reply->isFinished())
        QApplication::processEvents();

    return reply;
}

QNetworkReply *SyncNetworAccesskManager::sendCustomRequest(const QNetworkRequest &request, const QByteArray &verb, QIODevice *data)
{
    QNetworkReply* reply = QNetworkAccessManager::sendCustomRequest(request, verb, data);

    connect(reply, &QNetworkReply::errorOccurred, this, [=]
    {
        handleReplyError(reply);
    });

    while (!reply->isFinished())
        QApplication::processEvents();

    return reply;
}
