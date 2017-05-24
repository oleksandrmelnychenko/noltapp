#include "AddCollegueView.h"
#include "ui_AddCollegueView.h"

#include <QDebug>

AddCollegueView::AddCollegueView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::AddCollegueView)
{
    ui->setupUi(this);    
    SetValidationLabelsVisibility();

    mColleagueService = new ColleagueService(this);
    mAnimationController = new AnimationController();

    SubscribeToFormEvents();
}

AddCollegueView::~AddCollegueView()
{
    delete ui;
}

QString AddCollegueView::getInformationFromLineEdit(QLineEdit *lineEdit)
{
    return lineEdit->text();
}

void AddCollegueView::clearFocusOfLineEdits()
{
    ui->txtFirstName->clearFocus();
    ui->txtLastName->clearFocus();
    ui->txtEmail->clearFocus();
    ui->txtPhone->clearFocus();   
}

bool AddCollegueView::isLineEditEmpty(const QLineEdit *lineEdit)
{
    return (QString(lineEdit->text()).isEmpty());
}

void AddCollegueView::setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY)
{
    isLineEditEmpty(lineEdit) ? mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsStartPointY)
                            : mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsEndPointY);
}

void AddCollegueView::addCollegue()
{
    if(!IsLineEditsEmpty() && IsLineEditsValid())
    {
        QJsonObject json;
        json.insert("mFirstName", ui->txtFirstName->text());
        json.insert("mLastName", ui->txtLastName->text());
        json.insert("mEmail", ui->txtEmail->text());
        json.insert("mPhone", ui->txtPhone->text());
        json.insert("mDateOfBirth", ui->txtBirtday->text());

        RequestStatus(mColleagueService->CreateNewColleague(json));

        ui->btnAddCollegue->setEnabled(false);       
    }
    else
    {
        ui->lblIncorrectInput->setVisible(true);
    }
}

void AddCollegueView::validateLineEditInput(QLineEdit *lineEdit, QLabel *label, QString regPatern, bool *isValid)
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

void AddCollegueView::focusIn(QLineEdit *lineEdit, QLabel *label)
{
    lineEdit->setStyleSheet(mValidateColor);
    label->setVisible(false);
    ui->lblIncorrectInput->setVisible(false);
}

void AddCollegueView::RequestStatus(QJsonObject *status)
{
    emit requestStatus(status->value("Message").toString());
    ui->btnAddCollegue->setEnabled(true);
}

void AddCollegueView::clickColleague()
{
    emit clickColleaguelbl();
}

void AddCollegueView::SubscribeToFormEvents()
{
    connect(ui->btnAddCollegue, SIGNAL(clicked(bool)), this, SLOT(addCollegue()));
    connect(ui->lblCollegues, &ColleaguesLabel::pressIn, this, [this]{clickColleague();});

    connect(ui->lblFirstName, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtFirstName);});
    connect(ui->lblLastName, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtLastName);});
    connect(ui->lblEmail, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtEmail);});
    connect(ui->lblPhone, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtPhone);});
    connect(ui->lblBirthday, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtBirtday);});

    connect(ui->txtFirstName, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAnimation(ui->lblFirstName, mlblFirstNameEndPointY);
            focusIn(ui->txtFirstName, ui->lblIncorrectFirstName);});
    connect(ui->txtLastName, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAnimation(ui->lblLastName, mlblLastNameEndPointY);
            focusIn(ui->txtLastName, ui->lblIncorrectLastName);});
    connect(ui->txtEmail, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAnimation(ui->lblEmail, mlblEmailEndPointY);
            focusIn(ui->txtEmail, ui->lblIncorrectEmail);});
    connect(ui->txtPhone, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAnimation(ui->lblPhone, mlblPhoneEndPointY);
            focusIn(ui->txtPhone, ui->lblIncorrectPhone);});
    connect(ui->txtBirtday, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAnimation(ui->lblBirthday, mlblBirthdayEndPointY);
            focusIn(ui->txtPhone, ui->lblIncorrectBirthday);});

    connect(ui->txtFirstName, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditFirstName();
            validateLineEditInput(ui->txtFirstName, ui->lblIncorrectFirstName, mRegName, &isFirstNameValid);});
    connect(ui->txtLastName, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditLastName();
            validateLineEditInput(ui->txtLastName, ui->lblIncorrectLastName, mRegName, &isLastNameValid);});
    connect(ui->txtEmail, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditEmail();
            validateLineEditInput(ui->txtEmail, ui->lblIncorrectEmail, mRegEmail, &isEmailValid);});
    connect(ui->txtPhone, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditPhone();
            validateLineEditInput(ui->txtPhone, ui->lblIncorrectPhone, mRegPhone, &isPhoneValid);});
    connect(ui->txtBirtday, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnlineEditBirthday();
            validateLineEditInput(ui->txtBirtday, ui->lblIncorrectBirthday, mRegBirthday, &isBirthdayValid);});
}

void AddCollegueView::SetValidationLabelsVisibility()
{
    ui->lblIncorrectInput->setVisible(false);
    ui->lblIncorrectFirstName->setVisible(false);
    ui->lblIncorrectLastName->setVisible(false);
    ui->lblIncorrectEmail->setVisible(false);
    ui->lblIncorrectPhone->setVisible(false);
    ui->lblIncorrectBirthday->setVisible(false);
}

bool AddCollegueView::IsLineEditsEmpty()
{
    if(!getInformationFromLineEdit(ui->txtFirstName).isEmpty() && !getInformationFromLineEdit(ui->txtLastName).isEmpty() &&
            !getInformationFromLineEdit(ui->txtEmail).isEmpty() && !getInformationFromLineEdit(ui->txtPhone).isEmpty() &&
            !getInformationFromLineEdit(ui->txtBirtday).isEmpty())
    {
        return false;
    }
    return true;
}

bool AddCollegueView::IsLineEditsValid(){
    if(isFirstNameValid && isLastNameValid && isEmailValid && isPhoneValid && isBirthdayValid)
    {
        return true;
    }
    return false;
}

void AddCollegueView::setFocusOnLineEdit(QLineEdit *lineEdint)
{
    lineEdint->setFocus();    
    QMdiSubWindow::update();
}

void AddCollegueView::doLabelAnimation(QLabel *label, int labelsYCoordinate)
{
    mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsYCoordinate);    
    ui->widgetAddColleague->hide();
    ui->widgetAddColleague->show();
}

void AddCollegueView::lostFocusOnLineEditFirstName()
{
    setLabelsPosition(ui->txtFirstName, ui->lblFirstName, mlblFirstNameStartPointY, mlblFirstNameEndPointY);    
}

void AddCollegueView::lostFocusOnLineEditLastName()
{
    setLabelsPosition(ui->txtLastName, ui->lblLastName, mlblLastNameStartPointY, mlblLastNameEndPointY);
}

void AddCollegueView::lostFocusOnLineEditEmail()
{
    setLabelsPosition(ui->txtEmail, ui->lblEmail, mlblEmailStartPointY, mlblEmailEndPointY);
}

void AddCollegueView::lostFocusOnLineEditPhone()
{
    setLabelsPosition(ui->txtPhone, ui->lblPhone, mlblPhoneStartPointY, mlblPhoneEndPointY); // визивати напряму в конекті
}

void AddCollegueView::lostFocusOnlineEditBirthday()
{
    setLabelsPosition(ui->txtBirtday, ui->lblBirthday, mlblBirthdayStartPointY, mlblBirthdayEndPointY);
}


