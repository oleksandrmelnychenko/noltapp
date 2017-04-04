#include "AddCollegueView.h"
#include "ui_AddCollegueView.h"

#include <QDebug>

AddCollegueView::AddCollegueView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::AddCollegueView)
{
    ui->setupUi(this);

    connect(ui->btnAddCollegue, SIGNAL(clicked(bool)), this, SLOT(AddCollegue()));
    connect(ui->txtFirstName, SIGNAL(outFocus()),this, SLOT(validateFirstName()));
    connect(ui->txtLastName, SIGNAL(outFocus()), this, SLOT(validateLastName()));
    connect(ui->txtEmail, SIGNAL(outFocus()), this, SLOT(validateEmail()));
    connect(ui->txtPhone, SIGNAL(outFocus()), this, SLOT(validatePhone()));
}

AddCollegueView::~AddCollegueView()
{
    delete ui;
}

QString AddCollegueView::getInformationFromLineEdit(QLineEdit *lineEdit)
{
    return lineEdit->text();
}

void AddCollegueView::AddCollegue()
{
    QDate mCurrentDate = QDate::currentDate();
    PersonEntity currentCollegue(mCounter++, getInformationFromLineEdit(ui->txtNetUiId), mCurrentDate,
                                 getInformationFromLineEdit(ui->txtFirstName), getInformationFromLineEdit(ui->txtLastName),
                                 getInformationFromLineEdit(ui->txtEmail), getInformationFromLineEdit(ui->txtPhone));
    mColleguesVector << currentCollegue;
}

bool AddCollegueView::validateFirstName()
{
    QRegExp regName ("[a-zA-Z0-9_\\-\\.]{1,30}");
    bool validate = regName.exactMatch(ui->txtFirstName->text());

    if(validate)
    {

    }
    return validate;
}

bool AddCollegueView::validateLastName()
{
    QRegExp regName ("[a-zA-Z0-9_\\-\\.]{1,30}");
    bool validate = regName.exactMatch(ui->txtLastName->text());

    if(validate)
    {

    }
    return validate;
}

bool AddCollegueView::validateEmail()
{
    QRegExp regEmail ("([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_.-])+\\.([a-zA-Z]{2,4}|[0-9]{1,3})");
    bool validate = regEmail.exactMatch(ui->txtEmail->text());

    if(validate)
    {

    }
    return validate;
}

bool AddCollegueView::validatePhone()
{
    QRegExp regPhone ("\\([0-9]{3}\\)\\s[0-9]{3}-[0-9]{2}-[0-9]{2}");  // (097) 231-23-52
    bool validate = regPhone.exactMatch(ui->txtPhone->text());

    if(validate)
    {

    }
    return false;
}
