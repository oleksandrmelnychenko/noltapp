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

#include <Entities/PersonEntity.h>

class SalaryOperationRepository : public QObject
{
    Q_OBJECT
public:
    explicit SalaryOperationRepository(QNetworkAccessManager *networkManager, QObject *parent = 0);

signals:
    void getResultsFromRequestSalary(QJsonObject*);

public:    
    void GetPaymentHistoryById(long id);
    void PaidSalary(long id, QJsonObject pesron);

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager *mNetworkManager;
};

#endif // SALARYOPERATIONREPOSITORY_H
