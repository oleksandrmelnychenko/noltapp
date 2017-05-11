#include "UpdateCollegueView.h"
#include "ui_UpdateCollegueView.h"
#include <QMessageBox>

UpdateCollegueView::UpdateCollegueView(QWidget *parent,long id) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),    
    ui(new Ui::UpdateCollegueView),
    mId(id)
{
    ui->setupUi(this);
    ui->lblIncorrectInput->setVisible(false);
    ui->lblIncorrectFirstName->setVisible(false);
    ui->lblIncorrectLastName->setVisible(false);
    ui->lblIncorrectEmail->setVisible(false);
    ui->lblIncorrectPhone->setVisible(false);
    ui->lblIncorrectBirthday->setVisible(false);

    mRepository = new ColleagueOperationRepository(this);
    mAnimationController = new AnimationController();

    mRepository->GetColleagueById(id);

    SubscribeToFormEvents();
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
    ui->txtEditBirthday->setText(subtree.value("mDateOfBirth").toString());
}

void UpdateCollegueView::UpdateCollegue()
{
    if(!IsLineEditsEmpty() && IsLineEditsValid())
    {
        mJsonObject.insert("mFirstName",ui->txtEditFirstName->text());
        mJsonObject.insert("mLastName",ui->txtEditLastName->text());
        mJsonObject.insert("mEmail",ui->txtEditEmail->text());
        mJsonObject.insert("mPhone",ui->txtEditPhone->text());
        mJsonObject.insert("mDateOfBirth",ui->txtEditBirthday->text());

        mRepository->UpdateColleague(mJsonObject);

        connect(mRepository, SIGNAL(getResultsFromRequest(QJsonObject*)), this, SLOT(UpdateColleagueRequestStatus(QJsonObject*)));
    }
    else
    {
        ui->lblIncorrectInput->setVisible(true);
    }
}

void UpdateCollegueView::UpdateColleagueRequestStatus(QJsonObject *status)
{
    emit updateColleagueRequestStatus(status->value("Message").toString());
}

void UpdateCollegueView::DeleteColleagueRequestStatus(QJsonObject *status)
{    
    emit deleteColleagueRequestStatus(status->value("Message").toString());
    emit clickDeletelbl();
}

void UpdateCollegueView::clickColleague()
{
    emit clickColleaguelbl();
}

void UpdateCollegueView::clickDelete()
{
    mRepository->DeleteColleague(mId);
    connect(mRepository, SIGNAL(getResultsFromRequest(QJsonObject*)), this, SLOT(DeleteColleagueRequestStatus(QJsonObject*)));
}

void UpdateCollegueView::validateLineEditInput(QLineEdit *lineEdit, QLabel *label, QString regPatern, bool *isValid)
{
    QRegExp reg(regPatern);
    bool validate = reg.exactMatch(lineEdit->text());

    if(!validate)
    {
        *isValid = false;
        if(lineEdit->text().isEmpty())
        {
            lineEdit->setStyleSheet(mValidateColor);
        }
        else
        {
            lineEdit->setStyleSheet(mNotValidateColor);
            label->setVisible(true);
        }
    }
    else
    {
        *isValid = true;
        lineEdit->setStyleSheet(mValidateColor);
    }
}

void UpdateCollegueView::focusIn(QLineEdit *lineEdit, QLabel *label)
{
    lineEdit->setStyleSheet(mValidateColor);
    label->setVisible(false);
    ui->lblIncorrectInput->setVisible(false);
}

void UpdateCollegueView::SubscribeToFormEvents()
{
    connect(mRepository, SIGNAL(getResultsFromRequest(QJsonObject*)), this, SLOT(ResultFromRequest(QJsonObject*)));

    connect(ui->btnUpdate, SIGNAL(clicked(bool)), this, SLOT(UpdateCollegue()));
    connect(ui->lblDelete, &ColleaguesLabel::pressIn, this, [this]{clickDelete();});
    connect(ui->lblColleague, &ColleaguesLabel::pressIn, this, [this]{clickColleague();});

    connect(ui->lblFirstName, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtEditFirstName);});
    connect(ui->lblLastName, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtEditLastName);});
    connect(ui->lblEmail, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtEditEmail);});
    connect(ui->lblPhone, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtEditPhone);});
    connect(ui->lblBirthday, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtEditBirthday);});

    connect(ui->txtEditFirstName, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAniamtion(ui->lblFirstName, mlblFirstNameEndPointY);
            focusIn(ui->txtEditFirstName, ui->lblIncorrectFirstName);});
    connect(ui->txtEditLastName, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAniamtion(ui->lblLastName ,mlblLastNameEndPointY);
            focusIn(ui->txtEditLastName, ui->lblIncorrectLastName);});
    connect(ui->txtEditEmail, &ColleaguesLineEditd::inFocus,this,
            [this]{doLabelAniamtion(ui->lblEmail, mlblEmailEndPointY);
            focusIn(ui->txtEditEmail, ui->lblIncorrectEmail);});
    connect(ui->txtEditPhone, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAniamtion(ui->lblPhone, mlblPhoneEndPointY);
            focusIn(ui->txtEditPhone, ui->lblIncorrectPhone);});
    connect(ui->txtEditBirthday, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAniamtion(ui->lblBirthday, mlblBirthdatEndPointY);
            focusIn(ui->txtEditBirthday, ui->lblIncorrectBirthday);});

    connect(ui->txtEditFirstName, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditFirstName();
            validateLineEditInput(ui->txtEditFirstName, ui->lblIncorrectFirstName, mRegName, &isFirstNameValid);});
    connect(ui->txtEditLastName, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditLastName();
            validateLineEditInput(ui->txtEditLastName, ui->lblIncorrectLastName, mRegName, &isLastNameValid);});
    connect(ui->txtEditEmail, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditEmail();
            validateLineEditInput(ui->txtEditEmail, ui->lblIncorrectEmail, mRegEmail, &isEmailValid);});
    connect(ui->txtEditPhone, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditPhone();
            validateLineEditInput(ui->txtEditPhone, ui->lblIncorrectPhone, mRegPhone, &isPhoneValid);});
    connect(ui->txtEditBirthday, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditBirthday();
            validateLineEditInput(ui->txtEditBirthday, ui->lblIncorrectBirthday, mRegBirthday, &isBirthdayValid);});
}

QString UpdateCollegueView::getInformationFromLineEdit(QLineEdit *lineEdit)
{
    return lineEdit->text();
}

bool UpdateCollegueView::IsLineEditsEmpty()
{
    if(!getInformationFromLineEdit(ui->txtEditFirstName).isEmpty() && !getInformationFromLineEdit(ui->txtEditLastName).isEmpty() &&
            !getInformationFromLineEdit(ui->txtEditEmail).isEmpty() && !getInformationFromLineEdit(ui->txtEditPhone).isEmpty() &&
            !getInformationFromLineEdit(ui->txtEditBirthday).isEmpty())
    {
        return false;
    }
    return true;
}

bool UpdateCollegueView::IsLineEditsValid()
{
    if(isFirstNameValid && isLastNameValid && isEmailValid && isPhoneValid && isBirthdayValid)
    {
        return true;
    }
    return false;
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

void UpdateCollegueView::lostFocusOnLineEditBirthday()
{
    setLabelsPosition(ui->txtEditBirthday, ui->lblBirthday, mlblBirthdayStartPointY, mlblBirthdatEndPointY);
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
    isLineEditEmpty(lineEdit) ? mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsStartPointY)
                            : mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsEndPointY);
}

