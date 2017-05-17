#include "ColleagueService.h"

ColleagueService::ColleagueService(QObject *parent) : QObject(parent)
{
    mNetworkManager = new QNetworkAccessManager(this);
    mRepository = new ColleagueOperationRepository(mNetworkManager, this);

    connect(mRepository, SIGNAL(getResultsFromRequestColleague(QJsonObject*)), this, SLOT(ResultFromRequest(QJsonObject*)));
}

void ColleagueService::GetAllColleagues()
{
    mRepository->GetAllColleagues();
}

void ColleagueService::GetColleagueById(long id)
{
    mRepository->GetColleagueById(id);
}

void ColleagueService::CreateNewColleague(QJsonObject person)
{
    mRepository->CreateNewColleague(person);
}

void ColleagueService::UpdateColleague(QJsonObject person)
{
    mRepository->UpdateColleague(person);
}

void ColleagueService::DeleteColleague(long id)
{
    mRepository->DeleteColleague(id);
}

void ColleagueService::ResultFromRequest(QJsonObject *person)
{
    emit getResultsFromRequestColleague(person);
}

