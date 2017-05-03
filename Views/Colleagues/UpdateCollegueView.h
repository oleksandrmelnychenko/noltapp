#ifndef UPDATECOLLEGUEVIEW_H
#define UPDATECOLLEGUEVIEW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

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

protected slots:
    void ResultFromRequest(QJsonObject *result);
    void UpdateCollegue();

private slots:
    void SubscribeToFormEvents();
    void doLabelAniamtion(QLabel *label, int labelsYCoordinate);

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
    const int mlblPhoneStartPointY = 284;
    const int mlblPhoneEndPointY = 263;
};

#endif // UPDATECOLLEGUEVIEW_H
