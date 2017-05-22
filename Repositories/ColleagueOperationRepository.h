#ifndef COLLEAGUEOPERATIONREPOSITORY_H
#define COLLEAGUEOPERATIONREPOSITORY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

#include <Entities/PersonEntity.h>

class ColleagueOperationRepository : public QObject
{
    Q_OBJECT
public:
    explicit ColleagueOperationRepository(QNetworkAccessManager *networkManager, QObject *parent = 0);

signals:
    void getResultsFromRequestColleague(QJsonObject*);

public:
    void GetAllColleagues();
    void GetColleagueById(long id);
    void CreateNewColleague(QJsonObject person);
    void UpdateColleague(QJsonObject person);
    void DeleteColleague(long id);    

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager *mNetworkManager;

    const QString mGetAllColleagues = "http://noltwebapi.azurewebsites.net/api/v1/colleagues/all";
    const QString mCreateNewColleague = "http://noltwebapi.azurewebsites.net/api/v1/colleagues/new";
    const QString mUpdateColleague = "http://noltwebapi.azurewebsites.net/api/v1/colleagues/update";

    const std::string mGetColleagueById = "http://noltwebapi.azurewebsites.net/api/v1/colleagues/get?id=";
    const std::string mDeleteColleague = "http://noltwebapi.azurewebsites.net/api/v1/colleagues/delete?id=";
};

#endif // COLLEAGUEOPERATIONREPOSITORY_H
