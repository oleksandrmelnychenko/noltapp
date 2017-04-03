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
    title << "Id:";
    ui->tblWidgetId->setColumnCount(1);
    ui->tblWidgetId->setHorizontalHeaderLabels(title);

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
        PersonEntities b1 = mColleguesVector.at(i);
        QString s1 =  b1.getFirstName();

        ui->tblWidgetId->insertRow(ui->tblWidgetId->rowCount());
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 0, new QTableWidgetItem(s1));
    }
}

void ColleaguesForm::DoSmthWithObject(int row, int column)
{
    ui->tblWidgetId->setItem(row, column, new QTableWidgetItem("AZAZAZA"));
}


