#include "officeform.h"
#include "ui_officeform.h"

OfficeForm::OfficeForm(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::OfficeForm)
{
    ui->setupUi(this);
}

OfficeForm::~OfficeForm()
{
    delete ui;
}
