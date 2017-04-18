#include "AddCollegueView.h"
#include "ui_AddCollegueView.h"

#include <QDebug>

AddCollegueView::AddCollegueView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::AddCollegueView)
{
    ui->setupUi(this);    
    ui->lblIncorrectInput->hide();

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

void AddCollegueView::addCollegue()
{    
    QDate currentDate = QDate::currentDate();    

    if(!IsLineEditsEmpty() && IsLineEditsValid())
    {
        PersonEntity currentCollegue(mCounter++, getInformationFromLineEdit(ui->txtNetUiId), currentDate,
                                     getInformationFromLineEdit(ui->txtFirstName),
                                     getInformationFromLineEdit(ui->txtLastName),
                                     getInformationFromLineEdit(ui->txtEmail),
                                     getInformationFromLineEdit(ui->txtPhone));
        mColleguesVector << currentCollegue;
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
        lineEdit->text().isEmpty()?lineEdit->setStyleSheet(mValidateColor) : lineEdit->setStyleSheet(mNotValidateColor);
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

void AddCollegueView::SubscribeToFormEvents()
{
    connect(ui->btnAddCollegue, SIGNAL(clicked(bool)), this, SLOT(addCollegue()));

    connect(ui->txtFirstName, &ColleaguesLineEditd::outFocus, this,
            [this]{validateLineEditInput(ui->txtFirstName, mRegName, &isFirstNameValid);});
    connect(ui->txtLastName, &ColleaguesLineEditd::outFocus, this,
            [this]{validateLineEditInput(ui->txtLastName, mRegName, &isLastNameValid);});
    connect(ui->txtEmail, &ColleaguesLineEditd::outFocus, this,
            [this]{validateLineEditInput(ui->txtEmail, mRegEmail, &isEmailValid);});
    connect(ui->txtPhone, &ColleaguesLineEditd::outFocus, this,
            [this]{validateLineEditInput(ui->txtPhone, mRegPhone, &isPhoneValid);});

    connect(ui->txtFirstName, &ColleaguesLineEditd::inFocus, this, [this]{focusIn(ui->txtFirstName);});
    connect(ui->txtLastName, &ColleaguesLineEditd::inFocus, this, [this]{focusIn(ui->txtLastName);});
    connect(ui->txtEmail, &ColleaguesLineEditd::inFocus, this, [this]{focusIn(ui->txtEmail);});
    connect(ui->txtPhone, &ColleaguesLineEditd::inFocus, this, [this]{focusIn(ui->txtPhone);});
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


