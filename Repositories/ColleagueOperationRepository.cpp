#include "ColleagueOperationRepository.h"
#include <string>

ColleagueOperationRepository::ColleagueOperationRepository(QNetworkAccessManager *networkManager, QObject *parent)
    : mNetworkManager(networkManager),
      QObject(parent)
{    
    connect(mNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

void ColleagueOperationRepository::GetAllColleagues()
{
    QUrl url(mGetAllColleagues);
    QNetworkRequest request;
    request.setUrl(url);
    mNetworkManager->get(request);
}

void ColleagueOperationRepository::GetColleagueById(long id)
{
    std::string hostAndApi = mGetColleagueById;
    hostAndApi += std::to_string(id);

    QString qRequest = QString::fromStdString(hostAndApi);

    QUrl url(qRequest);
    QNetworkRequest request;
    request.setUrl(url);
    mNetworkManager->get(request);
}

void ColleagueOperationRepository::CreateNewColleague(QJsonObject person)
{
    QUrl url(mCreateNewColleague);
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    QJsonDocument doc;
    doc.setObject(person);

    QByteArray request_body = doc.toJson();

    mNetworkManager->post(request,request_body);
}

void ColleagueOperationRepository::UpdateColleague(QJsonObject person)
{    
    QUrl url(mUpdateColleague);
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    QJsonDocument doc;
    doc.setObject(person);

    QByteArray request_body = doc.toJson();

    mNetworkManager->post(request,request_body);

    //    QNetworkReply *reply = mNetworkManager->post(request,request_body);
    //    qDebug() << reply;
}

void ColleagueOperationRepository::DeleteColleague(long id)
{
    std::string hostAndApi = mDeleteColleague;
    hostAndApi += std::to_string(id);;

    QString qRequest = QString::fromStdString(hostAndApi);

    QUrl url(qRequest);
    QNetworkRequest request;
    request.setUrl(url);
    mNetworkManager->deleteResource(request);
}

void ColleagueOperationRepository::replyFinished(QNetworkReply *reply)
{
    if(!reply->error())
    {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();

        emit getResultsFromRequestColleague(&root);
    }
}
