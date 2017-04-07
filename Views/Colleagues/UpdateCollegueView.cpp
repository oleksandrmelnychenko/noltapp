#include "UpdateCollegueView.h"
#include "ui_UpdateCollegueView.h"

UpdateCollegueView::UpdateCollegueView(QWidget *parent,long id) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::UpdateCollegueView),
    mIdUpdatedCollegue(id)
{
    ui->setupUi(this);
    ui->txtEditFirstName->setText(QString::number(id));
}

UpdateCollegueView::~UpdateCollegueView()
{
    delete ui;
}
