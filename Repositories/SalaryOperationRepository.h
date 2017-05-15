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
    explicit SalaryOperationRepository(QObject *parent = 0);

signals:
    //void getResultsFromRequest(QJsonObject*);

public:


public slots:
    //void replyFinished(QNetworkReply* reply);
};

#endif // SALARYOPERATIONREPOSITORY_H
