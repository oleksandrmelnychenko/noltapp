#ifndef ADDCOLLEGUEVIEW_H
#define ADDCOLLEGUEVIEW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QVector>
#include <QLabel>
#include <QUuid>
#include <QDate>
#include <QLineEdit>
#include <QJsonObject>
#include <QMdiArea>

#include "Entities/PersonEntity.h"
#include "CommonUiControllers/AnimationController.h"
#include "Services/ColleagueService.h"

namespace Ui {
    class AddCollegueView;
}

class AddCollegueView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit AddCollegueView(QWidget *parent = 0);
    ~AddCollegueView();

signals:
    void requestStatus(const QString&);
    void clickColleaguelbl();

private:
    void clearFocusOfLineEdits();
    bool isLineEditEmpty(const QLineEdit *lineEdit);
    void setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY);

protected slots:
    void addCollegue();    
    void clickColleague();

private:
    void RequestStatus(QJsonObject *status);

    void SubscribeToFormEvents();
    void SetValidationLabelsVisibility();

    QString getInformationFromLineEdit(QLineEdit *lineEdit);
    bool IsLineEditsEmpty();
    bool IsLineEditsValid();

private slots:
    void focusIn(QLineEdit *lineEdit, QLabel *label);
    void validateLineEditInput(QLineEdit *lineEdit, QLabel *label, QString regPatern, bool *isValid);
    void setFocusOnLineEdit(QLineEdit *lineEdint);
    void doLabelAnimation(QLabel *label, int labelsYCoordinate);
    void lostFocusOnLineEdit(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY);

private:
    Ui::AddCollegueView *ui;

    ColleagueService *mColleagueService;

    QString mRegName = ("[a-zA-Z0-9_\\-\\.]{1,30}");
    QString mRegEmail = ("([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_.-])+\\.([a-zA-Z]{2,4}|[0-9]{1,3})");
    QString mRegPhone = ("[0-9]{10}"); //("\\([0-9]{3}\\)\\s[0-9]{3}-[0-9]{2}-[0-9]{2}");
    QString mRegBirthday = ("[0-3]?[0-9].[0-3]?[0-9].([0-9]{2})?[0-9]{2}");

    QString mValidateColor = ("border:none; border-bottom:1px solid #909090; color:#ffffff; padding-left:7px;");
    QString mNotValidateColor = ("border:none;border-bottom:1px solid #ff2306; color:#ffffff; padding-left:7px;");

    bool isFirstNameValid = false;
    bool isLastNameValid = false;
    bool isEmailValid = false;
    bool isPhoneValid = false;
    bool isBirthdayValid = false;

    AnimationController* mAnimationController;
    int mAnimationDuration = 250;    

    const int mlblFirstNameStartPointY = 113;
    const int mlblFirstNameEndPointY = 92;

    const int mlblLastNameStartPointY = 170;
    const int mlblLastNameEndPointY = 149;

    const int mlblEmailStartPointY = 227;
    const int mlblEmailEndPointY = 206;

    const int mlblPhoneStartPointY = 283;
    const int mlblPhoneEndPointY = 262;

    const int mlblBirthdayStartPointY = 339;
    const int mlblBirthdayEndPointY = 318;
};

#endif // ADDCOLLEGUEVIEW_H
