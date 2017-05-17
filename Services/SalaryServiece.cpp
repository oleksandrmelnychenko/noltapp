#include "SalaryServiece.h"

SalaryServiece::SalaryServiece(QObject *parent) : QObject(parent)
{
    mNetworkManager = new QNetworkAccessManager(this);
    mColleagueRepository = new ColleagueOperationRepository(mNetworkManager, this);
    mSalaryOperationRepository = new SalaryOperationRepository(mNetworkManager, this);

    connect(mColleagueRepository, SIGNAL(getResultsFromRequestColleague(QJsonObject*)),
            this, SLOT(ResultFromRequestColleague(QJsonObject*)), Qt::UniqueConnection);
    connect(mSalaryOperationRepository, SIGNAL(getResultsFromRequestSalary(QJsonObject*)),
            this, SLOT(ResultFromRequestSalary(QJsonObject*)), Qt::UniqueConnection);
}

void SalaryServiece::GetAllColleagues()
{
    mColleagueRepository->GetAllColleagues();
}

void SalaryServiece::GetColleagueById(long id)
{
    mColleagueRepository->GetColleagueById(id);
}

void SalaryServiece::UpdateColleague(QJsonObject person)
{
    mColleagueRepository->UpdateColleague(person);
}

void SalaryServiece::GetPaymentHistoryById(long id)
{
    mSalaryOperationRepository->GetPaymentHistoryById(id);
}

void SalaryServiece::PaidSalary(long id, QJsonObject person)
{
    mSalaryOperationRepository->PaidSalary(id, person);
}

void SalaryServiece::ResultFromRequestColleague(QJsonObject *person)
{
    emit getResultsFromRequestColleague(person);
}

void SalaryServiece::ResultFromRequestSalary(QJsonObject *salary)
{
    emit getResultsFromRequestSalary(salary);
}
