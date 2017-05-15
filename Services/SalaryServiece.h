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

    void GetAllColleagues();
    void GetColleagueById(long id);
    void GetPaymentHistoryById(long id);
    void PaidSalary(long id, QJsonObject person);

signals:
    void getResultsFromRequest(QJsonObject*);

public slots:
    void ResultFromRequest(QJsonObject *person);

private:
    ColleagueOperationRepository *mColleagueRepository;
    SalaryOperationRepository *mSalaryOperationRepository;
    QNetworkAccessManager *mNetworkManager;
};

#endif // SALARYSERVIECE_H
