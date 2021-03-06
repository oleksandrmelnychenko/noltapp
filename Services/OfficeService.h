#ifndef OFFICESERVICE_H
#define OFFICESERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>

#include "Entities/PersonEntity.h"
#include "Repositories/OfficeOpearationRepository.h"

class OfficeService : public QObject
{
    Q_OBJECT
public:
    explicit OfficeService(QObject *parent = 0);

signals:
    void getOfficePaymentHistoryFinished();
    void getOfficePaymentHistory(QJsonObject*);

public slots:
    void GetOfficePaymentHistory();

public:
    QJsonObject* CreateNewOfficePayment(QJsonObject payment);

private:
    OfficeOpearationRepository *mOfficOperationRepository;
    QNetworkAccessManager *mNetworkManager;
};

#endif // OFFICESERVICE_H
