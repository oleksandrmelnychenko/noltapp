#ifndef SALARYOPERATIONREPOSITORY_H
#define SALARYOPERATIONREPOSITORY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QEventLoop>

#include <Entities/PersonEntity.h>

class SalaryOperationRepository : public QObject
{
    Q_OBJECT
public:
    explicit SalaryOperationRepository(QNetworkAccessManager *networkManager, QObject *parent = 0);

public:
    QJsonObject* GetPaymentHistoryById(long id);
    QJsonObject* PaidSalary(long id, QJsonObject salary);

protected:
    void replyFinished(QNetworkReply* reply);

    QJsonObject mResult;

private:
    QNetworkAccessManager *mNetworkManager;

    const std::string mGetPaymentHistoryById = "http://noltwebapi.azurewebsites.net/api/v1/salaries/all?id=";
    const std::string mPaidSalary = "http://noltwebapi.azurewebsites.net/api/v1/salaries/new?id=    ";
};

#endif // SALARYOPERATIONREPOSITORY_H
