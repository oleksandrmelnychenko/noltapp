#include "ColleaguesView.h"
#include "ui_ColleaguesView.h"

#include <QDebug>
#include <QStandardItemModel>

ColleaguesForm::ColleaguesForm(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::ColleaguesForm)
{
    ui->setupUi(this);

    QStringList titleId;
    titleId << "Id:";
    ui->tblWidgetId->setColumnCount(1);
    ui->tblWidgetId->setHorizontalHeaderLabels(titleId);

    QStringList titleCurrentCollegue;
    titleCurrentCollegue << "NetUI Id" << "Create date" << "Name" << "Surname" << "Email" << "Phone";
    ui->tblWidgetCurrentColleague->setColumnCount(6);
    ui->tblWidgetCurrentColleague->setHorizontalHeaderLabels(titleCurrentCollegue);



    connect(ui->btnLoadData, SIGNAL(clicked(bool)), SLOT(LoadData()));
    connect(ui->tblWidgetId,  SIGNAL(cellClicked(int,int)), this, SLOT(DoSmthWithObject(int, int)));

    QDate d(2017,3,4);
    PersonEntities bob(1,"bob123", d, "Bob", "Arum", "bob@gmail.com", "097554822");
    PersonEntities jack(2,"jack123", d, "Jack", "Partak", "partak@gmail.com", "0967324234");
    PersonEntities rachel(3,"rachel123", d, "Rachel", "Valera", "rv@gmail.com", "0775464523");
    PersonEntities korky(4,"korky123", d, "Korky", "Melloun", "korky@gmail.com", "097544962");
    PersonEntities jose(5,"jose123", d, "Jose", "Mour", "jm@gmail.com", "097678912");

    mColleguesVector << bob << jack << rachel << korky << jose;
}

ColleaguesForm::~ColleaguesForm()
{
    delete ui;
}

void ColleaguesForm::LoadData()
{
    for(int i = 0; i != mColleguesVector.size(); i++)
    {
        PersonEntities currentCollegue = mColleguesVector.at(i);
        QString currentCollegueId = QString::number(currentCollegue.Id());

        ui->tblWidgetId->insertRow(ui->tblWidgetId->rowCount());
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 0, new QTableWidgetItem(currentCollegueId));
    }
}

void ColleaguesForm::DoSmthWithObject(int row, int column)
{
    mCurrentCollegue = mColleguesVector.at(row);

    ui->tblWidgetCurrentColleague->removeRow(0);

    ui->tblWidgetCurrentColleague->insertRow(ui->tblWidgetCurrentColleague->rowCount()); // or 0
    ui->tblWidgetCurrentColleague->setItem(0, 0, new QTableWidgetItem(mCurrentCollegue.NetUiID().toString()));
    ui->tblWidgetCurrentColleague->setItem(0, 1, new QTableWidgetItem(mCurrentCollegue.CreateDate().toString()));
    ui->tblWidgetCurrentColleague->setItem(0, 2, new QTableWidgetItem(mCurrentCollegue.getFirstName()));
    ui->tblWidgetCurrentColleague->setItem(0, 3, new QTableWidgetItem(mCurrentCollegue.getLastName()));
    ui->tblWidgetCurrentColleague->setItem(0, 4, new QTableWidgetItem(mCurrentCollegue.getEmail()));
    ui->tblWidgetCurrentColleague->setItem(0, 5, new QTableWidgetItem(mCurrentCollegue.getPhone()));


    //ui->tblWidgetCurrentColleague->insertRow(ui->tblWidgetCurrentColleague->rowCount());
    //ui->tblWidgetId->setItem(row, column, new QTableWidgetItem("AZAZAZA"));
}


