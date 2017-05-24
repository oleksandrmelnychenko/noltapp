#ifndef COLLEAGUESERVICE_H
#define COLLEAGUESERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>

#include "Entities/PersonEntity.h"
#include "Repositories/ColleagueOperationRepository.h"

class ColleagueService : public QObject
{
    Q_OBJECT
public:
    explicit ColleagueService(QObject *parent = 0);

    QJsonObject *GetAllColleagues();
    QJsonObject *GetColleagueById(long id);
    QJsonObject* CreateNewColleague(QJsonObject person);
    QJsonObject *UpdateColleague(QJsonObject person);
    QJsonObject* DeleteColleague(long id);

private:
    QNetworkAccessManager *mNetworkManager;
    ColleagueOperationRepository *mRepository;
};

#endif // COLLEAGUESERVICE_H
