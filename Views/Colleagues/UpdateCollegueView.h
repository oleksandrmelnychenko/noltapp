#ifndef UPDATECOLLEGUEVIEW_H
#define UPDATECOLLEGUEVIEW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QLineEdit>

#include "Repositories/ColleagueOperationRepository.h"
#include "Entities/PersonEntity.h"
#include "CommonUiControllers/AnimationController.h"

namespace Ui {
    class UpdateCollegueView;
}

class UpdateCollegueView : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit UpdateCollegueView(QWidget *parent = 0, long id = 0);
    ~UpdateCollegueView();

signals:
    void updateColleagueRequestStatus(const QString&);
    void deleteColleagueRequestStatus(const QString&);
    void clickColleaguelbl();
    void clickDeletelbl();

protected slots:
    void ResultFromRequest(QJsonObject *result);
    void UpdateCollegue();
    void UpdateColleagueRequestStatus(QJsonObject* status);
    void DeleteColleagueRequestStatus(QJsonObject* status);
    void clickColleague();
    void clickDelete();

private slots:    
    void validateLineEditInput(QLineEdit *lineEdit, QString regPatern, bool *isValid);

    void focusIn(QLineEdit *lineEdit);

    void doLabelAniamtion(QLabel *label, int labelsYCoordinate);

    void lostFocusOnLineEditFirstName();
    void lostFocusOnLineEditLastName();
    void lostFocusOnLineEditEmail();
    void lostFocusOnLineEditPhone();

private:
    void SubscribeToFormEvents();

    QString getInformationFromLineEdit(QLineEdit *lineEdit);
    bool IsLineEditsEmpty();
    bool IsLineEditsValid();

    void setFocusOnLineEdit(QLineEdit *lineEdint);
    bool isLineEditEmpty(const QLineEdit *lineEdit);
    void setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY);

private:
    Ui::UpdateCollegueView *ui;

    ColleagueOperationRepository *mRepository;
    QJsonObject mJsonObject;

    QString mRegName = ("[a-zA-Z0-9_\\-\\.]{1,30}");
    QString mRegEmail = ("([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_.-])+\\.([a-zA-Z]{2,4}|[0-9]{1,3})");
    QString mRegPhone = ("\\([0-9]{3}\\)\\s[0-9]{3}-[0-9]{2}-[0-9]{2}");  // (097) 231-23-52;

    QString mValidateColor = ("border:none; border-bottom:1px solid #909090; color:#ffffff; padding-left:7px;");
    QString mNotValidateColor = ("border:none;border-bottom:1px solid #ff2306; color:#ffffff; padding-left:7px;");

    long mId;

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

#endif // UPDATECOLLEGUEVIEW_H
