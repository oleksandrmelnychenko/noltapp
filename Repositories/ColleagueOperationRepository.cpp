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
    QUrl url("http://noltwebapi.azurewebsites.net/api/v1/colleagues/get?id=2");
    QNetworkRequest request;
    request.setUrl(url);
    mNetworkManager->get(request);
}

void ColleagueOperationRepository::CreateNewColleague(PersonEntity *person)
{
    //std::string
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

        qDebug() << root;
        emit getResultsFromRequest(root);
    }
}
