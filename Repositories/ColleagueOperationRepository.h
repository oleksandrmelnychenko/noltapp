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
    explicit ColleagueOperationRepository(QObject *parent = 0);

signals:
    void getResultsFromRequest(QJsonObject*);

public slots:
    void GetAllColleagues();
    void GetColleagueById(long id);
    void CreateNewColleague(QJsonObject person);
    void UpdateColleague(QJsonObject person);
    void DeleteColleague(long id);

    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager *mNetworkManager;
};

#endif // COLLEAGUEOPERATIONREPOSITORY_H
