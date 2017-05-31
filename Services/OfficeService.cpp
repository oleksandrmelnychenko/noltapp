#include "OfficeService.h"

OfficeService::OfficeService(QObject *parent) : QObject(parent)
{
    mNetworkManager = new QNetworkAccessManager(this);
    mOfficOperationRepository = new OfficeOpearationRepository(mNetworkManager, this);
}

QJsonObject* OfficeService::GetOfficePaymentHistory()
{
    return mOfficOperationRepository->GetOfficePaymentHistory();
}

QJsonObject* OfficeService::CreateNewOfficePayment(QJsonObject payment)
{
    return mOfficOperationRepository->CreateNewOfficePayment(payment);
}
