#ifndef OFFICEFORM_H
#define OFFICEFORM_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QScrollBar>
#include <QGridLayout>

#include "Entities/PersonEntity.h"
#include "CommonUiControllers/AnimationController.h"

namespace Ui {
    class OfficeForm;
}

class OfficeView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit OfficeView(QWidget *parent = 0);
    ~OfficeView();

private:
    void SubscribeToFormEvents();

    void SetPaymentHistoryColumnOptions();

    bool isLineEditEmpty(const QLineEdit *lineEdit);
    void setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY);

private slots:
    void PaidSalary();

    void setFocusOnLineEdit(QLineEdit *lineEdint);
    void focusIn(QLineEdit *lineEdit, QLabel *label);
    void doLabelAnimation(QLabel *label, int labelsYCoordinate);
    void lostFocusOnLineEdit(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY);
    void validateLineEditInput(QLineEdit *lineEdit, QLabel *label, QString regPatern, bool *isValid);

private:
    Ui::OfficeForm *ui;

    QString mRegPayment = ("[0-9]{1,5}(\\.[0-9]{1,2})?");

    QString mValidateColor = ("border:none; border-bottom:1px solid #909090; color:#ffffff; padding-left:7px;");
    QString mNotValidateColor = ("border:none;border-bottom:1px solid #ff2306; color:#ffffff; padding-left:7px;");

    bool isPaymentValid = false;

    AnimationController* mAnimationController;
    int mAnimationDuration = 250;

    int mCurrentColleagueId = 0;

    const int mlblPaymentStartPointY = 31;
    const int mlblPaymentEndPointY = 10;

};

#endif // OFFICEFORM_H
