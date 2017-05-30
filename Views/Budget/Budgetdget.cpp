#include "Budget.h"
#include "ui_Budget.h"

Budget::Budget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Budget)
{
    ui->setupUi(this);
}

Budget::~Budget()
{
    delete ui;
}
