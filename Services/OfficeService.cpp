#include "OfficeService.h"

OfficeService::OfficeService(QObject *parent) : QObject(parent)
{
    mNetworkManager = new QNetworkAccessManager(this);
    mOfficOperationRepository = new OfficeOpearationRepository(mNetworkManager, this);
}

void OfficeService::GetOfficePaymentHistory()
{
    emit getOfficePaymentHistory(mOfficOperationRepository->GetOfficePaymentHistory());
    emit getOfficePaymentHistoryFinished();
}

QJsonObject* OfficeService::CreateNewOfficePayment(QJsonObject payment)
{
    return mOfficOperationRepository->CreateNewOfficePayment(payment);
}
