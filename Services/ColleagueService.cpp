#include "ColleagueService.h"

ColleagueService::ColleagueService(QObject *parent) : QObject(parent)
{
    mNetworkManager = new QNetworkAccessManager(this);
    mRepository = new ColleagueOperationRepository(mNetworkManager, this);
}

QJsonObject* ColleagueService::GetAllColleagues()
{
    return mRepository->GetAllColleagues();
}

QJsonObject* ColleagueService::GetColleagueById(long id)
{
    return mRepository->GetColleagueById(id);
}

QJsonObject* ColleagueService::CreateNewColleague(QJsonObject person)
{
    return mRepository->CreateNewColleague(person);
}

QJsonObject* ColleagueService::UpdateColleague(QJsonObject person)
{
    return mRepository->UpdateColleague(person);
}

QJsonObject* ColleagueService::DeleteColleague(long id)
{
    return mRepository->DeleteColleague(id);
}

