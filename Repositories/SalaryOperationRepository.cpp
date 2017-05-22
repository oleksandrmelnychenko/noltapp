#include "SalaryOperationRepository.h"
#include <QDebug>

SalaryOperationRepository::SalaryOperationRepository(QNetworkAccessManager *networkManager, QObject *parent)
    : mNetworkManager(networkManager),
      QObject(parent)
{
    connect(mNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

void SalaryOperationRepository::GetPaymentHistoryById(long id)
{
    std::string hostAndApi = "http://noltwebapi.azurewebsites.net/api/v1/salaries/all?id=";
    hostAndApi += std::to_string(id);

    QString qRequest = QString::fromStdString(hostAndApi);

    QUrl url(qRequest);
    QNetworkRequest request;
    request.setUrl(url);
    mNetworkManager->get(request);
}

void SalaryOperationRepository::PaidSalary(long id, QJsonObject salary)
{
    std::string hostAndApi = "http://noltwebapi.azurewebsites.net/api/v1/salaries/new?id=";
    hostAndApi += std::to_string(id);

    QString qRequest = QString::fromStdString(hostAndApi);

    QUrl url(qRequest);
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    QJsonDocument doc;
    doc.setObject(salary);

    QByteArray request_body = doc.toJson();

    mNetworkManager->post(request,request_body);
}

void SalaryOperationRepository::replyFinished(QNetworkReply *reply)
{
    if(!reply->error())
    {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();        

        emit getResultsFromRequestSalary(&root);
    }
}
