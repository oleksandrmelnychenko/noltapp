#include "ColleagueService.h"

ColleagueService::ColleagueService(QObject *parent) : QObject(parent)
{
    mNetworkManager = new QNetworkAccessManager(this);
    mRepository = new ColleagueOperationRepository(mNetworkManager, this);
}

void ColleagueService::GetAllColleagues()
{
    emit getAllColleagues(mRepository->GetAllColleagues());
    emit getAllColleaguesFinished();
}

QJsonObject* ColleagueService::GetColleagueById(long id)
{
    //emit getColleagueByIdFinished(mRepository->GetColleagueById(id));
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

