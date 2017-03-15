#include "SalaryView.h"
#include "ui_salaryform.h"

SalaryForm::SalaryForm(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::SalaryForm)
{
    ui->setupUi(this);
}

SalaryForm::~SalaryForm()
{
    delete ui;
}
