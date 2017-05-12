#ifndef SALARYFORM_H
#define SALARYFORM_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QLineEdit>

#include "Entities/PersonEntity.h"
#include "CommonUiControllers/AnimationController.h"
#include "Repositories/ColleagueOperationRepository.h"

namespace Ui {
    class SalaryForm;
}

class SalaryView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit SalaryView(QWidget *parent = 0);
    ~SalaryView();

private:
    void SubscribeToFormEvents();

    QString getInformationFromLineEdit(QLineEdit *lineEdit);

    void clearFocusOfLineEdits();
    bool isLineEditEmpty(const QLineEdit *lineEdit);
    void setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY);

public slots:


private slots:
    void RequestStatus(QJsonObject *status);
    void focusIn(QLineEdit *lineEdit, QLabel *label);
    void validateLineEditInput(QLineEdit *lineEdit, QLabel *label, QString regPatern, bool *isValid);
    void setFocusOnLineEdit(QLineEdit *lineEdint);
    void doLabelAnimation(QLabel *label, int labelsYCoordinate);
    void lostFocusOnLineEditSalary();
    void lostFocusOnLineEditPayment();

signals:
    void requestStatus(const QString&);

private:
    Ui::SalaryForm *ui;

    ColleagueOperationRepository *mRepository;

    QString mRegSalary = ("[0-9]{3,5}(\\.[0-9]{1,2})?");
    QString mRegPayment = ("[0-9]{1,5}(\\.[0-9]{1,2})?");

    QString mValidateColor = ("border:none; border-bottom:1px solid #909090; color:#ffffff; padding-left:7px;");
    QString mNotValidateColor = ("border:none;border-bottom:1px solid #ff2306; color:#ffffff; padding-left:7px;");

    bool isSalaryValid = true;
    bool isPaymentValid = false;

    AnimationController* mAnimationController;
    int mAnimationDuration = 250;

    const int mlblSalaryStartPointY = 31;
    const int mlblSalaryEndPointY = 10;
    const int mlblPaymentStartPointY = 188;
    const int mlblPaymentEndPointY = 167;

};

#endif // SALARYFORM_H
