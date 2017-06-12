#include "BudgetService.h"

BudgetService::BudgetService(QObject *parent) : QObject(parent)
{
    mNetworkManager = new QNetworkAccessManager(this);
    mBudgetRepository = new BudgetOperationRepository(mNetworkManager, this);
}

void BudgetService::GetBudgetHistory()
{
    emit getBudgetHistory(mBudgetRepository->GetBudgetHistory());
    emit getBudgetHistoryFinished();
}

QJsonObject *BudgetService::GetBudgetById(long id)
{
    return mBudgetRepository->GetBudgetById(id);
}

QJsonObject* BudgetService::CreateNewBudget(QJsonObject payment)
{
    return mBudgetRepository->CreateNewBudget(payment);
}
