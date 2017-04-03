#include "OfficeView.h"
#include "ui_OfficeView.h"

OfficeView::OfficeView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::OfficeForm)
{
    ui->setupUi(this);
}

OfficeView::~OfficeView()
{
    delete ui;
}
