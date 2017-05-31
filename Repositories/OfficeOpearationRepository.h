#ifndef OFFICEOPEARATIONREPOSITORY_H
#define OFFICEOPEARATIONREPOSITORY_H

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

class OfficeOpearationRepository : public QObject
{
    Q_OBJECT
public:
    explicit OfficeOpearationRepository(QNetworkAccessManager *networkManager, QObject *parent = 0);

public:
    QJsonObject* GetOfficePaymentHistory();
    QJsonObject* CreateNewOfficePayment(QJsonObject payment);

protected:
    void replyFinished(QNetworkReply* reply);

    QJsonObject mResult;

private:
    QNetworkAccessManager *mNetworkManager;

    const QString mGetOfficePaymentHistory = "";
    const QString mCreateNewOfficePayment = "";
};

#endif // OFFICEOPEARATIONREPOSITORY_H
