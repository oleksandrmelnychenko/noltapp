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
    void requestStatus(const QString&);

protected slots:
    void ResultFromRequest(QJsonObject *result);
    void UpdateCollegue();
    void RequestStatus(QJsonObject* status);

private slots:
    void SubscribeToFormEvents();
    void doLabelAniamtion(QLabel *label, int labelsYCoordinate);

    void lostFocusOnLineEditFirstName();
    void lostFocusOnLineEditLastName();
    void lostFocusOnLineEditEmail();
    void lostFocusOnLineEditPhone();

private:
    bool isLineEditEmpty(const QLineEdit *lineEdit);
    void setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY);

private:
    Ui::UpdateCollegueView *ui;

    ColleagueOperationRepository *mRepository;
    QJsonObject mJsonObject;

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
