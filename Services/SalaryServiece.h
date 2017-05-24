#ifndef SALARYSERVIECE_H
#define SALARYSERVIECE_H

#include <QObject>
#include <QNetworkAccessManager>

#include "Entities/PersonEntity.h"
#include "Repositories/ColleagueOperationRepository.h"
#include "Repositories/SalaryOperationRepository.h"

class SalaryServiece : public QObject
{
    Q_OBJECT
public:
    explicit SalaryServiece(QObject *parent = 0);

    QJsonObject* GetAllColleagues();
    QJsonObject *GetColleagueById(long id);
    QJsonObject* UpdateColleague(QJsonObject person);
    QJsonObject* GetPaymentHistoryById(long id);
    QJsonObject* PaidSalary(long id, QJsonObject salary);

private:
    ColleagueOperationRepository *mColleagueRepository;
    SalaryOperationRepository *mSalaryOperationRepository;
    QNetworkAccessManager *mNetworkManager;
};

#endif // SALARYSERVIECE_H
