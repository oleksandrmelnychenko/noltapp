#include "UpdateCollegueView.h"
#include "ui_UpdateCollegueView.h"
#include <QMessageBox>

UpdateCollegueView::UpdateCollegueView(QWidget *parent,long id) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    mId(id),
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

void UpdateCollegueView::clickColleague()
{
    emit clickColleaguelbl();
}

void UpdateCollegueView::clickDelete()
{
    mRepository->DeleteColleague(mId);
    emit clickDeletelbl();
}

void UpdateCollegueView::SubscribeToFormEvents()
{
    connect(ui->lblFirstName, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtEditFirstName);});
    connect(ui->lblLastName, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtEditLastName);});
    connect(ui->lblEmail, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtEditEmail);});
    connect(ui->lblPhone, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtEditPhone);});

    connect(ui->txtEditFirstName,&ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAniamtion(ui->lblFirstName, mlblFirstNameEndPointY);});
    connect(ui->txtEditLastName,&ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAniamtion(ui->lblLastName,mlblLastNameEndPointY);});
    connect(ui->txtEditEmail,&ColleaguesLineEditd::inFocus,this,
            [this]{doLabelAniamtion(ui->lblEmail,mlblEmailEndPointY);});
    connect(ui->txtEditPhone,&ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAniamtion(ui->lblPhone,mlblPhoneEndPointY);});

    connect(ui->txtEditFirstName, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditFirstName();});
    connect(ui->txtEditLastName, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditLastName();});
    connect(ui->txtEditEmail, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditEmail();});
    connect(ui->txtEditPhone, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditPhone();});

    connect(ui->lblColleague, &ColleaguesLabel::pressIn, this, [this]{clickColleague();});
    connect(ui->lblDelete, &ColleaguesLabel::pressIn, this, [this]{clickDelete();});
}

void UpdateCollegueView::doLabelAniamtion(QLabel *label, int labelsYCoordinate)
{
    mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsYCoordinate);

    ui->widgetUpdateColleague->hide();
    ui->widgetUpdateColleague->show();
}

void UpdateCollegueView::lostFocusOnLineEditFirstName()
{
    setLabelsPosition(ui->txtEditFirstName, ui->lblFirstName, mlblFirstNameStartPointY, mlblFirstNameEndPointY);
}

void UpdateCollegueView::lostFocusOnLineEditLastName()
{
    setLabelsPosition(ui->txtEditLastName, ui->lblLastName, mlblLastNameStartPointY, mlblLastNameEndPointY);
}

void UpdateCollegueView::lostFocusOnLineEditEmail()
{
    setLabelsPosition(ui->txtEditEmail, ui->lblEmail, mlblEmailStartPointY, mlblEmailEndPointY);
}

void UpdateCollegueView::lostFocusOnLineEditPhone()
{
    setLabelsPosition(ui->txtEditPhone, ui->lblPhone, mlblPhoneStartPointY, mlblPhoneEndPointY);
}

void UpdateCollegueView::setFocusOnLineEdit(QLineEdit *lineEdint)
{
    lineEdint->setFocus();
}

bool UpdateCollegueView::isLineEditEmpty(const QLineEdit *lineEdit)
{
    return (QString(lineEdit->text()).isEmpty());
}

void UpdateCollegueView::setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY)
{
    if(isLineEditEmpty(lineEdit))
    {
        mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsStartPointY);
    }
    else
    {
        mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsEndPointY);
    }
}

