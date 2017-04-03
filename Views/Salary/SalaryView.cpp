#include "SalaryView.h"
#include "ui_SalaryView.h"

SalaryView::SalaryView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::SalaryForm)
{
    ui->setupUi(this);
}

SalaryView::~SalaryView()
{
    delete ui;
}
