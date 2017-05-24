#include "ColleagueOperationRepository.h"
#include <string>
#include <QThread>

ColleagueOperationRepository::ColleagueOperationRepository(QNetworkAccessManager *networkManager, QObject *parent)
    : mNetworkManager(networkManager),
      QObject(parent)
{  
}

QJsonObject* ColleagueOperationRepository::GetAllColleagues()
{
    QUrl url(mGetAllColleagues);
    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply *reply = mNetworkManager->get(request);    
    replyFinished(reply);

    return &mResult;
}

QJsonObject* ColleagueOperationRepository::GetColleagueById(long id)
{
    std::string hostAndApi = mGetColleagueById;
    hostAndApi += std::to_string(id);

    QString qRequest = QString::fromStdString(hostAndApi);

    QUrl url(qRequest);
    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply *reply = mNetworkManager->get(request);   
    replyFinished(reply);

    return &mResult;
}

QJsonObject *ColleagueOperationRepository::CreateNewColleague(QJsonObject person)
{
    QUrl url(mCreateNewColleague);
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

QJsonObject* ColleagueOperationRepository::UpdateColleague(QJsonObject person)
{    
    QUrl url(mUpdateColleague);
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

QJsonObject *ColleagueOperationRepository::DeleteColleague(long id)
{
    std::string hostAndApi = mDeleteColleague;
    hostAndApi += std::to_string(id);;

    QString qRequest = QString::fromStdString(hostAndApi);

    QUrl url(qRequest);
    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply *reply = mNetworkManager->deleteResource(request);
    replyFinished(reply);

    return &mResult;
}

void ColleagueOperationRepository::replyFinished(QNetworkReply *reply)
{    
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(!reply->error())
    {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        mResult = document.object(); // check if the object has old data
    }
}
