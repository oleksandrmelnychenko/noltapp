#include "HistoryView.h"
#include "ui_HistoryView.h"

HistoryView::HistoryView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryView)
{
    ui->setupUi(this);
}

HistoryView::~HistoryView()
{
    delete ui;
}
