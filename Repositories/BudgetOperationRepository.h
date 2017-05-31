#ifndef BUDGETOPERATIONREPOSITORY_H
#define BUDGETOPERATIONREPOSITORY_H

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

class BudgetOperationRepository : public QObject
{
    Q_OBJECT
public:
    explicit BudgetOperationRepository(QNetworkAccessManager *networkManager, QObject *parent = 0);

public:
    QJsonObject* GetBudgetHistory();
    QJsonObject* CreateNewBudget(QJsonObject payment);

protected:
    void replyFinished(QNetworkReply* reply);

    QJsonObject mResult;

private:
    QNetworkAccessManager *mNetworkManager;

    const QString mGetBudgetHistory = "";
    const QString mCreateNewBudget = "";
};

#endif // BUDGETOPERATIONREPOSITORY_H
