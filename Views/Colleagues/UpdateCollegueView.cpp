#include "UpdateCollegueView.h"
#include "ui_UpdateCollegueView.h"
#include <QMessageBox>

UpdateCollegueView::UpdateCollegueView(QWidget *parent,long id) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::UpdateCollegueView)
{
    ui->setupUi(this);
    mRepository = new ColleagueOperationRepository(this);
    mAnimationController = new AnimationController();

    mRepository->GetColleagueById(id);

    SubscribeToFormEvents();

    connect(mRepository, SIGNAL(getResultsFromRequest(QJsonObject*)), this, SLOT(ResultFromRequest(QJsonObject*)));
    connect(ui->btnUpdate, SIGNAL(clicked(bool)), this, SLOT(UpdateCollegue()));
}

UpdateCollegueView::~UpdateCollegueView()
{
    delete ui;
}

void UpdateCollegueView::ResultFromRequest(QJsonObject *result)
{
    QJsonValue jv = result->value("Body");
    QJsonObject subtree = jv.toObject();

    mJsonObject = subtree;

    ui->txtEditFirstName->setText(subtree.value("mFirstName").toString());
    ui->txtEditLastName->setText(subtree.value("mLastName").toString());
    ui->txtEditEmail->setText(subtree.value("mEmail").toString());
    ui->txtEditPhone->setText(subtree.value("mPhone").toString());
}

void UpdateCollegueView::UpdateCollegue()
{
    mJsonObject.insert("mFirstName",ui->txtEditFirstName->text());
    mJsonObject.insert("mLastName",ui->txtEditLastName->text());
    mJsonObject.insert("mEmail",ui->txtEditEmail->text());
    mJsonObject.insert("mPhone",ui->txtEditPhone->text());

    mRepository->UpdateColleague(mJsonObject);

    connect(mRepository, SIGNAL(getResultsFromRequest(QJsonObject*)), this, SLOT(RequestStatus(QJsonObject*)));
}

void UpdateCollegueView::RequestStatus(QJsonObject *status)
{
    emit requestStatus(status->value("Message").toString());
}

void UpdateCollegueView::SubscribeToFormEvents()
{
    connect(ui->txtEditFirstName,&ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAniamtion(ui->lblFirstName, mlblFirstNameEndPointY);});
    connect(ui->txtEditLastName,&ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAniamtion(ui->lblLastName,mlblLastNameEndPointY);});


}

void UpdateCollegueView::doLabelAniamtion(QLabel *label, int labelsYCoordinate)
{
    mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsYCoordinate);

    ui->widgetUpdateColleague->hide();
    ui->widgetUpdateColleague->show();
}

