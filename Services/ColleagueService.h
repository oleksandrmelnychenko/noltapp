#ifndef COLLEAGUESERVICE_H
#define COLLEAGUESERVICE_H

#include <QObject>
#include <QNetworkAccessManager>

#include "Entities/PersonEntity.h"
#include "Repositories/ColleagueOperationRepository.h"

class ColleagueService : public QObject
{
    Q_OBJECT
public:
    explicit ColleagueService(QObject *parent = 0);

    void GetAllColleagues();
    void GetColleagueById(long id);
    void CreateNewColleague(QJsonObject person);
    void UpdateColleague(QJsonObject person);
    void DeleteColleague(long id);

signals:
    void getResultsFromRequestColleague(QJsonObject*);

public slots:
    void ResultFromRequest(QJsonObject *person);

private:
    ColleagueOperationRepository *mRepository;
    QNetworkAccessManager *mNetworkManager;
};

#endif // COLLEAGUESERVICE_H
