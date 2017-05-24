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
#include <QEventLoop>

#include <Entities/PersonEntity.h>

class ColleagueOperationRepository : public QObject
{
    Q_OBJECT
public:
    explicit ColleagueOperationRepository(QNetworkAccessManager *networkManager, QObject *parent = 0);

public:
    QJsonObject* GetAllColleagues();
    QJsonObject* GetColleagueById(long id);
    QJsonObject* CreateNewColleague(QJsonObject person);
    QJsonObject* UpdateColleague(QJsonObject person);
    QJsonObject* UpdateColleagueSalaty(QJsonObject salary);
    QJsonObject* DeleteColleague(long id);

protected:
    void replyFinished(QNetworkReply* reply);

    QJsonObject mResult;    

private:
    QNetworkAccessManager *mNetworkManager;

    const QString mGetAllColleagues = "http://noltwebapi.azurewebsites.net/api/v1/colleagues/all";
    const QString mCreateNewColleague = "http://noltwebapi.azurewebsites.net/api/v1/colleagues/new";
    const QString mUpdateColleague = "http://noltwebapi.azurewebsites.net/api/v1/colleagues/update";
    const QString mUpdateColleagueSalary ="http://noltwebapi.azurewebsites.net/api/v1/colleagues/update/salary";

    const std::string mGetColleagueById = "http://noltwebapi.azurewebsites.net/api/v1/colleagues/get?id=";
    const std::string mDeleteColleague = "http://noltwebapi.azurewebsites.net/api/v1/colleagues/delete?id=";
};

#endif // COLLEAGUEOPERATIONREPOSITORY_H
