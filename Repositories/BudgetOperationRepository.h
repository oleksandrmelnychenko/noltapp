#ifndef BUDGETOPERATIONREPOSITORY_H
#define BUDGETOPERATIONREPOSITORY_H

#include <QObject>

class BudgetOperationRepository : public QObject
{
    Q_OBJECT
public:
    explicit BudgetOperationRepository(QObject *parent = 0);

signals:

public slots:
};

#endif // BUDGETOPERATIONREPOSITORY_H