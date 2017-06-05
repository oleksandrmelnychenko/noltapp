#include "CurrentBudgetInformationView.h"
#include "ui_CurrentBudgetInformationView.h"

CurrentBudgetInformationView::CurrentBudgetInformationView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentBudgetInformationView)
{
    ui->setupUi(this);
}

CurrentBudgetInformationView::~CurrentBudgetInformationView()
{
    delete ui;
}
