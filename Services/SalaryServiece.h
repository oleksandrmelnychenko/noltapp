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

signals:
    void getAllColleaguesFinished();
    void getAllColleagues(QJsonObject*);

public slots:
    void GetAllColleagues();

public:
    QJsonObject* GetColleagueById(long id);
    QJsonObject* UpdateColleagueSalary(QJsonObject person);
    QJsonObject* GetPaymentHistoryById(long id);
    QJsonObject* PaidSalary(long id, QJsonObject salary);

private:
    ColleagueOperationRepository *mColleagueRepository;
    SalaryOperationRepository *mSalaryOperationRepository;
    QNetworkAccessManager *mNetworkManager;
};

#endif // SALARYSERVIECE_H
