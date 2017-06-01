#include "OfficeOpearationRepository.h"

OfficeOpearationRepository::OfficeOpearationRepository(QNetworkAccessManager *networkManager, QObject *parent)
    : mNetworkManager(networkManager),
      QObject(parent)
{

}

QJsonObject *OfficeOpearationRepository::GetOfficePaymentHistory()
{
    QUrl url(mGetOfficePaymentHistory);
    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply *reply = mNetworkManager->get(request);
    replyFinished(reply);

    return &mResult;
}

QJsonObject *OfficeOpearationRepository::CreateNewOfficePayment(QJsonObject payment)
{
    QUrl url(mCreateNewOfficePayment);
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    QJsonDocument doc;
    doc.setObject(payment);

    QByteArray request_body = doc.toJson();

    QNetworkReply *reply = mNetworkManager->post(request,request_body);
    replyFinished(reply);

    return &mResult;
}

void OfficeOpearationRepository::replyFinished(QNetworkReply *reply)
{
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(!reply->error())
    {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        mResult = document.object();
    }
}
