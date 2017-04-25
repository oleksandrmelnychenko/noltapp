#include "ColleagueOperationRepository.h"
#include <string>
#include <QDebug>

ColleagueOperationRepository::ColleagueOperationRepository(QObject *parent) : QObject(parent)
{
    mNetworkManager = new QNetworkAccessManager(this);
    connect(mNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

void ColleagueOperationRepository::GetAllColleagues()
{
    QUrl url("http://noltwebapi.azurewebsites.net/api/v1/colleagues/all");
    QNetworkRequest request;
    request.setUrl(url);
    mNetworkManager->get(request);
}

void ColleagueOperationRepository::GetColleagueById(long id)
{
    std::string hostAndApi = "http://noltwebapi.azurewebsites.net/api/v1/colleagues/get?id=";
    hostAndApi += std::to_string(id);;

    QString qRequest = QString::fromStdString(hostAndApi);

    QUrl url(qRequest);
    QNetworkRequest request;
    request.setUrl(url);
    mNetworkManager->get(request);
}

void ColleagueOperationRepository::CreateNewColleague(PersonEntity *person)
{

}

void ColleagueOperationRepository::UpdateColleague(long id, PersonEntity *person)
{

}

void ColleagueOperationRepository::DeleteColleague(long id)
{

}

void ColleagueOperationRepository::replyFinished(QNetworkReply *reply)
{
    if(!reply->error())
    {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject *root = &document.object();

        emit getResultsFromRequest(root);
    }
}
