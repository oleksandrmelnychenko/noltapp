#include "SalaryServiece.h"

SalaryServiece::SalaryServiece(QObject *parent) : QObject(parent)
{
    mNetworkManager = new QNetworkAccessManager(this);
    mColleagueRepository = new ColleagueOperationRepository(mNetworkManager, this);
    mSalaryOperationRepository = new SalaryOperationRepository(mNetworkManager, this);
}

QJsonObject* SalaryServiece::GetAllColleagues()
{    
    return mColleagueRepository->GetAllColleagues();
}

QJsonObject* SalaryServiece::GetColleagueById(long id)
{
    return mColleagueRepository->GetColleagueById(id);
}

QJsonObject* SalaryServiece::UpdateColleagueSalary(QJsonObject person)
{
    return mColleagueRepository->UpdateColleagueSalaty(person);
}

QJsonObject* SalaryServiece::GetPaymentHistoryById(long id)
{
    return mSalaryOperationRepository->GetPaymentHistoryById(id);
}

QJsonObject* SalaryServiece::PaidSalary(long id, QJsonObject salary)
{
    return mSalaryOperationRepository->PaidSalary(id, salary);
}
