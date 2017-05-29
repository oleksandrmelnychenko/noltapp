#include "OfficeView.h"
#include "ui_OfficeView.h"

OfficeView::OfficeView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::OfficeForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

OfficeView::~OfficeView()
{
    delete ui;
}
