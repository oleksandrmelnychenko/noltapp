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

QJsonObject *BudgetOperationRepository::GetBudgetById(long id)
{
    std::string hostAndApi = mGetBudgetById;
    hostAndApi += std::to_string(id);

    QString qRequest = QString::fromStdString(hostAndApi);

    QUrl url(qRequest);
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
    doc.setObject(payment);

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
