#include "AddCollegueView.h"
#include "ui_AddCollegueView.h"

#include <QDebug>

AddCollegueView::AddCollegueView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::AddCollegueView)
{
    ui->setupUi(this);

    connect(ui->btnAddCollegue, SIGNAL(clicked(bool)), this, SLOT(AddCollegue()));
}

AddCollegueView::~AddCollegueView()
{
    delete ui;
}

QUuid AddCollegueView::getNetUiId()
{
    return ui->txtNetUiId->text();
}

QString AddCollegueView::getFirstName()
{
    return ui->txtFirstName->text();
}

QString AddCollegueView::getLastName()
{
    return ui->txtLastName->text();
}

QString AddCollegueView::getEmail()
{
    return ui->txtEmail->text();
}

QString AddCollegueView::getPhone()
{
    return ui->txtPhone->text();
}

void AddCollegueView::AddCollegue()
{
    QDate mCurrentDate = QDate::currentDate();
    PersonEntity currentCollegue(mCounter++, getNetUiId(), mCurrentDate, getFirstName(), getLastName(), getEmail(), getPhone());
    mColleguesVector << currentCollegue;
    //qDebug() << mColleguesVector;
}
