#ifndef BUDGETSERVICE_H
#define BUDGETSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>

#include "Entities/PersonEntity.h"
#include "Repositories/BudgetOperationRepository.h"

class BudgetService : public QObject
{
    Q_OBJECT
public:
    explicit BudgetService(QObject *parent = 0);

signals:
    void getBudgetHistoryFinished();
    void getBudgetHistory(QJsonObject*);

public slots:
    void GetBudgetHistory();

public:
    QJsonObject *GetBudgetById(long id);
    QJsonObject* CreateNewBudget(QJsonObject payment);

private:
    BudgetOperationRepository *mBudgetRepository;
    QNetworkAccessManager *mNetworkManager;
};

#endif // BUDGETSERVICE_H
