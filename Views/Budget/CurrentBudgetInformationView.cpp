#include "CurrentBudgetInformationView.h"
#include "ui_CurrentBudgetInformationView.h"

CurrentBudgetInformationView::CurrentBudgetInformationView(QWidget *parent, long id) :
    QMdiSubWindow(parent,  Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::CurrentBudgetInformationView),
    mId(id)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

CurrentBudgetInformationView::~CurrentBudgetInformationView()
{
    delete ui;
}
