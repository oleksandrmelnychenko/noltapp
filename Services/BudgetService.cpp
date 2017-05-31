#include "BudgetService.h"

BudgetService::BudgetService(QObject *parent) : QObject(parent)
{
    mNetworkManager = new QNetworkAccessManager(this);
    mBudgetRepository = new BudgetOperationRepository(mNetworkManager, this);
}

QJsonObject* BudgetService::GetBudgetHistory()
{
    return mBudgetRepository->GetBudgetHistory();
}

QJsonObject* BudgetService::CreateNewBudget(QJsonObject payment)
{
    return mBudgetRepository->CreateNewBudget(payment);
}
