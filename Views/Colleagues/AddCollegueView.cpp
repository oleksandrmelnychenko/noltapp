#include "AddCollegueView.h"
#include "ui_AddCollegueView.h"

#include <QDebug>

AddCollegueView::AddCollegueView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::AddCollegueView)
{
    ui->setupUi(this);    
    ui->lblIncorrectInput->hide();
    mRepository = new ColleagueOperationRepository(this);
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
    if(isLineEditEmpty(lineEdit))
    {
        mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsStartPointY);       
    }
    else
    {
        mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsEndPointY);       
    }    
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

        mRepository->CreateNewColleague(json);

        connect(mRepository, SIGNAL(getResultsFromRequest(QJsonObject*)), this, SLOT(RequestStatus(QJsonObject*)));
    }
    else
    {
        ui->lblIncorrectInput->show();
    }
}

void AddCollegueView::validateLineEditInput(QLineEdit *lineEdit, QString regPatern, bool *isValid)
{
    QRegExp reg(regPatern);
    bool validate = reg.exactMatch(lineEdit->text());

    if(!validate)
    {
        *isValid = false;
        lineEdit->text().isEmpty()?lineEdit->setStyleSheet(mValidateColor)
                                 : lineEdit->setStyleSheet(mNotValidateColor);
        // output invalid input message
    }
    else
    {
        *isValid = true;
        lineEdit->setStyleSheet(mValidateColor);
    }
}

void AddCollegueView::focusIn(QLineEdit *lineEdit)
{
    lineEdit->setStyleSheet(mValidateColor);
    ui->lblIncorrectInput->hide();
    QMdiSubWindow::update();
}

void AddCollegueView::RequestStatus(QJsonObject *status)
{
    emit requestStatus(status->value("Message").toString());
}

void AddCollegueView::clickColleague()
{
    emit clickColleaguelbl();
}

void AddCollegueView::SubscribeToFormEvents()
{
    connect(ui->btnAddCollegue, SIGNAL(clicked(bool)), this, SLOT(addCollegue()));

    connect(ui->lblFirstName, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtFirstName);});
    connect(ui->lblLastName, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtLastName);});
    connect(ui->lblEmail, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtEmail);});
    connect(ui->lblPhone, &ColleaguesLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtPhone);});

    connect(ui->txtFirstName, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAnimation(ui->lblFirstName, mlblFirstNameEndPointY); focusIn(ui->txtFirstName);});
    connect(ui->txtLastName, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAnimation(ui->lblLastName, mlblLastNameEndPointY); focusIn(ui->txtLastName);});
    connect(ui->txtEmail, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAnimation(ui->lblEmail, mlblEmailEndPointY); focusIn(ui->txtEmail);});
    connect(ui->txtPhone, &ColleaguesLineEditd::inFocus, this,
            [this]{doLabelAnimation(ui->lblPhone, mlblPhoneEndPointY); focusIn(ui->txtPhone);});

    connect(ui->txtFirstName, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditFirstName(); validateLineEditInput(ui->txtFirstName, mRegName, &isFirstNameValid);});
    connect(ui->txtLastName, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditLastName(); validateLineEditInput(ui->txtLastName, mRegName, &isLastNameValid);});
    connect(ui->txtEmail, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditEmail(); validateLineEditInput(ui->txtEmail, mRegEmail, &isEmailValid);});
    connect(ui->txtPhone, &ColleaguesLineEditd::outFocus, this,
            [this]{lostFocusOnLineEditPhone(); validateLineEditInput(ui->txtPhone, mRegPhone, &isPhoneValid);});

    connect(ui->lblCollegues, &ColleaguesLabel::pressIn, this, [this]{clickColleague();});
}

bool AddCollegueView::IsLineEditsEmpty()
{
    if(!getInformationFromLineEdit(ui->txtFirstName).isEmpty() && !getInformationFromLineEdit(ui->txtLastName).isEmpty() &&
            !getInformationFromLineEdit(ui->txtEmail).isEmpty() && !getInformationFromLineEdit(ui->txtPhone).isEmpty())
    {
        return false;
    }
    return true;
}

bool AddCollegueView::IsLineEditsValid(){
    if(isFirstNameValid && isLastNameValid && isEmailValid && isPhoneValid)
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


