#include "SalaryOperationRepository.h"
#include <QDebug>

SalaryOperationRepository::SalaryOperationRepository(QNetworkAccessManager *networkManager, QObject *parent)
    : mNetworkManager(networkManager),
      QObject(parent)
{    
}

QJsonObject *SalaryOperationRepository::GetPaymentHistoryById(long id)
{
    std::string hostAndApi = mGetPaymentHistoryById;
    hostAndApi += std::to_string(id);

    QString qRequest = QString::fromStdString(hostAndApi);

    QUrl url(qRequest);
    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply *reply = mNetworkManager->get(request);
    replyFinished(reply);

    return &mResult;
}

QJsonObject* SalaryOperationRepository::PaidSalary(long id, QJsonObject salary)
{
    std::string hostAndApi = mPaidSalary;
    hostAndApi += std::to_string(id);

    QString qRequest = QString::fromStdString(hostAndApi);

    QUrl url(qRequest);
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    QJsonDocument doc;
    doc.setObject(salary);

    QByteArray request_body = doc.toJson();

    QNetworkReply *reply =  mNetworkManager->post(request,request_body);
    replyFinished(reply);

    return &mResult;
}

void SalaryOperationRepository::replyFinished(QNetworkReply *reply)
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
