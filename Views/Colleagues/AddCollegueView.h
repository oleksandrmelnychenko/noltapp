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
#include "Repositories/ColleagueOperationRepository.h"

namespace Ui {
    class AddCollegueView;
}

class AddCollegueView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit AddCollegueView(QWidget *parent = 0);
    ~AddCollegueView();    

    QString getInformationFromLineEdit(QLineEdit *lineEdit);

signals:
    void requestStatus(const QString&);
    void clickColleaguelbl();

private:
    void clearFocusOfLineEdits();
    bool isLineEditEmpty(const QLineEdit *lineEdit);
    void setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY);

protected slots:
    void addCollegue();
    void validateLineEditInput(QLineEdit *lineEdit, QString regPatern, bool *isValid);
    void focusIn(QLineEdit *lineEdit);
    void RequestStatus(QJsonObject *status);
    void clickColleague();

protected:    
    void SubscribeToFormEvents();
    bool IsLineEditsEmpty();
    bool IsLineEditsValid();

private slots:
    void setFocusOnLineEdit(QLineEdit *lineEdint);
    void doLabelAnimation(QLabel *label, int labelsYCoordinate);
    void lostFocusOnLineEditFirstName();
    void lostFocusOnLineEditLastName();
    void lostFocusOnLineEditEmail();
    void lostFocusOnLineEditPhone();   

private:
    Ui::AddCollegueView *ui;

    ColleagueOperationRepository *mRepository;
    //QVector<PersonEntity> mColleguesVector;
    int mCounter = 0;    

    QString mRegName = ("[a-zA-Z0-9_\\-\\.]{1,30}");
    QString mRegEmail = ("([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_.-])+\\.([a-zA-Z]{2,4}|[0-9]{1,3})");
    QString mRegPhone = ("\\([0-9]{3}\\)\\s[0-9]{3}-[0-9]{2}-[0-9]{2}");  // (097) 231-23-52;

    QString mValidateColor = ("border:none; border-bottom:1px solid #909090; color:#ffffff; padding-left:7px;");
    QString mNotValidateColor = ("border:none;border-bottom:1px solid #ff2306; color:#ffffff; padding-left:7px;");

    bool isFirstNameValid = false;
    bool isLastNameValid = false;
    bool isEmailValid = false;
    bool isPhoneValid = false;

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

};

#endif // ADDCOLLEGUEVIEW_H
