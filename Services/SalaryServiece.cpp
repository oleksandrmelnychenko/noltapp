#include "SalaryServiece.h"

SalaryServiece::SalaryServiece(QObject *parent) : QObject(parent)
{
    mNetworkManager = new QNetworkAccessManager(this);
    mColleagueRepository = new ColleagueOperationRepository(mNetworkManager, this);
    mSalaryOperationRepository = new SalaryOperationRepository(mNetworkManager, this);

    connect(mColleagueRepository, SIGNAL(getResultsFromRequest(QJsonObject*)), this, SLOT(ResultFromRequest(QJsonObject*)));
    connect(mSalaryOperationRepository, SIGNAL(getResultsFromRequest(QJsonObject*)), this, SLOT(ResultFromRequest(QJsonObject*)));
}

void SalaryServiece::GetAllColleagues()
{
    mColleagueRepository->GetAllColleagues();
}

void SalaryServiece::GetColleagueById(long id)
{
    mColleagueRepository->GetColleagueById(id);
}

void SalaryServiece::GetPaymentHistoryById(long id)
{
    mSalaryOperationRepository->GetPaymentHistoryById(id);
}

void SalaryServiece::PaidSalary(long id, QJsonObject person)
{
    mSalaryOperationRepository->PaidSalary(id, person);
}

void SalaryServiece::ResultFromRequest(QJsonObject *person)
{
    emit getResultsFromRequest(person);
}
