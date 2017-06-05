#ifndef BUDGETVIEW_H
#define BUDGETVIEW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QScrollBar>
#include <QGridLayout>
#include <QLabel>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QLineEdit>

#include "Entities/PersonEntity.h"
#include "CommonUiControllers/AnimationController.h"
#include "Services/BudgetService.h"

namespace Ui {
    class BudgetView;
}

class BudgetView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit BudgetView(QWidget *parent = 0);
    ~BudgetView();

signals:
    void setBudgetRequestStatus(const QString&);
    void watchCurrentBudgetInformation(long id);

private:
    void SubscribeToFormEvents();

    void SetBudgetHistoryColumnOptions();
    void FillBudgetTable(QJsonObject *result);

    void SetBudgetStatus(QJsonObject *status);

    bool isLineEditEmpty(const QLineEdit *lineEdit);
    void setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY);

private slots:
    void AddBudget();
    void WatchCurrentBudgetInformation(int row, int column);

    void setFocusOnLineEdit(QLineEdit *lineEdint);
    void focusIn(QLineEdit *lineEdit, QLabel *label);
    void doLabelAnimation(QLabel *label, int labelsYCoordinate);
    void lostFocusOnLineEdit(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY);
    void validateLineEditInput(QLineEdit *lineEdit, QLabel *label, QString regPatern, bool *isValid);

private:
    Ui::BudgetView *ui;

    BudgetService *mBudgetService;
    QJsonObject mJsonObjectBudget;

    QString mRegBudget = ("[0-9]{1,5}(\\.[0-9]{1,2})?");

    QString mValidateColor = ("border:none; border-bottom:1px solid #909090; color:#ffffff; padding-left:7px;");
    QString mNotValidateColor = ("border:none;border-bottom:1px solid #ff2306; color:#ffffff; padding-left:7px;");

    bool isBudgetnValid = false;

    AnimationController* mAnimationController;
    int mAnimationDuration = 250;

    const int mlblBudgetStartPointY = 31;
    const int mlblBudgetEndPointY = 10;
};

#endif // BUDGETVIEW_H
