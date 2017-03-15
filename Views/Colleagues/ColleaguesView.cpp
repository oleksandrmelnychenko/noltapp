#include "ColleaguesView.h"
#include "ui_colleaguesform.h"

ColleaguesForm::ColleaguesForm(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::ColleaguesForm)
{
    ui->setupUi(this);
}

ColleaguesForm::~ColleaguesForm()
{
    delete ui;
}
