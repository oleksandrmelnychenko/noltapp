#include "ColleaguesView.h"
#include "ui_ColleaguesView.h"

#include <QDebug>
#include <QStandardItemModel>

ColleaguesForm::ColleaguesForm(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::ColleaguesForm)
{
    ui->setupUi(this);

    QStringList title;
    title << "Names:";
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderLabels(title);

    connect(ui->btnChangeLabel, SIGNAL(clicked(bool)), SLOT(ChangeLabel()));
    connect(ui->btnLoadData, SIGNAL(clicked(bool)), SLOT(LoadData()));
    connect(ui->tableWidget,  SIGNAL(cellClicked(int,int)), this, SLOT(DoSmthWithObject(int, int)));

    Colleagues bob1("Bob");
    Colleagues jack1("Jack");
    Colleagues rachel1("Rachel");

    mColleguesVector << bob1 << jack1 << rachel1;
}

ColleaguesForm::~ColleaguesForm()
{
    delete ui;
}

void ColleaguesForm::ChangeLabel()
{
    if(mCounter >= mColleguesVector.size())
        mCounter = 0;

    Colleagues b1 = mColleguesVector.at(mCounter);
    QString s1 = b1.getName();
    ui->label->setText(s1);

    mCounter++;
}

void ColleaguesForm::LoadData()
{
    QStandardItemModel *model = new QStandardItemModel(3,0,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Names:")));

    for(int i = 0; i != mColleguesVector.size(); i++)
    {
        Colleagues b1 = mColleguesVector.at(i);
        QString s1 =  b1.getName();

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()- 1, 0, new QTableWidgetItem(s1));

        QModelIndex index = model->index(i,0,QModelIndex());
        model->setData(index,s1);
        ui->tableView->setModel(model);
    }
}

void ColleaguesForm::DoSmthWithObject(int row, int column)
{
    ui->tableWidget->setItem(row, column, new QTableWidgetItem("AZAZAZA"));
}


