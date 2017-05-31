#include "BudgetOperationRepository.h"

BudgetOperationRepository::BudgetOperationRepository(QNetworkAccessManager *networkManager, QObject *parent)
    : mNetworkManager(networkManager),
      QObject(parent)
{

}

QJsonObject *BudgetOperationRepository::GetBudgetHistory()
{
    QUrl url(mGetBudgetHistory);
    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply *reply = mNetworkManager->get(request);
    replyFinished(reply);

    return &mResult;
}

QJsonObject *BudgetOperationRepository::CreateNewBudget(QJsonObject payment)
{
    QUrl url(mCreateNewBudget);
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    QJsonDocument doc;
    doc.setObject(person);

    QByteArray request_body = doc.toJson();

    QNetworkReply *reply = mNetworkManager->post(request,request_body);
    replyFinished(reply);

    return &mResult;
}

void BudgetOperationRepository::replyFinished(QNetworkReply *reply)
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
