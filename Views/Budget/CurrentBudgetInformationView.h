#ifndef CURRENTBUDGETINFORMATIONVIEW_H
#define CURRENTBUDGETINFORMATIONVIEW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QLineEdit>
#include <QScrollBar>

#include <Services/BudgetService.h>
#include "CommonUiControllers/Views/Budget/budgettype.h"

namespace Ui {
    class CurrentBudgetInformationView;
}

class CurrentBudgetInformationView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit CurrentBudgetInformationView(QWidget *parent = 0, long id = 0);
    ~CurrentBudgetInformationView();

private:
    void SetTableColumnOptions();
    void FillCurrentRow(QJsonObject *subtree, BudgetType budgetType);
    void FillCurrentBudgetTable(QJsonObject *result);

private:
    Ui::CurrentBudgetInformationView *ui;

    QJsonObject mJsonObject;
    BudgetService *mBudgetService;

    long mId;
};

#endif // CURRENTBUDGETINFORMATIONVIEW_H
