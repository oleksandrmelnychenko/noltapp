#include "ColleaguesView.h"
#include "ui_ColleaguesView.h"

#include <QDebug>
#include <QStandardItemModel>

ColleaguesView::ColleaguesView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::ColleaguesForm)
{
    ui->setupUi(this);

    QStringList titleId;
    titleId << "ID" << "NET UI ID" << "CREATE DATE" << "UPDATE DATE" << "FIRST NAME" << "LAST NAME" << "EMAIL" << "PHONE";
    ui->tblWidgetId->setColumnCount(8);
    ui->tblWidgetId->setHorizontalHeaderLabels(titleId);    
    ui->tblWidgetId->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tblWidgetId->verticalHeader()->setVisible(false);
    //ui->tblWidgetId->setAlternatingRowColors(true); //one row one color second another    

    connect(ui->tblWidgetId,  SIGNAL(cellClicked(int,int)), this, SLOT(DoSmthWithObject(int, int)));
    connect(ui->lblAddNew, SIGNAL(pressIn()), this, SLOT(CreateAddCollegueView()));

    QDate d = QDate::currentDate();
    PersonEntity bob(1,"bob123", d, "Bob", "Arum", "bob@gmail.com", "097554822");
    PersonEntity jack(2,"jack123", d, "Jack", "Partak", "partak@gmail.com", "0967324234");
    PersonEntity rachel(3,"rachel123", d, "Rachel", "Valera", "rv@gmail.com", "0775464523");
    PersonEntity korky(4,"korky123", d, "Korky", "Melloun", "korky@gmail.com", "097544962");
    PersonEntity jose(5,"jose123", d, "Jose", "Mour", "jm@gmail.com", "097678912");

    mColleguesVector << bob << jack << rachel << korky << jose;

    LoadData();
}

ColleaguesView::~ColleaguesView()
{
    delete ui;
}

void ColleaguesView::LoadData()
{
    for(int i = 0; i != mColleguesVector.size(); i++)
    {
        PersonEntity currentCollegue = mColleguesVector.at(i);
        QString currentCollegueId = QString::number(currentCollegue.Id());

        SetTableColumnsWidth();
        ui->tblWidgetId->insertRow(ui->tblWidgetId->rowCount());
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 0, new QTableWidgetItem(currentCollegueId));
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 1, new QTableWidgetItem(currentCollegue.NetUiID().toString()));
        //ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 2, new QTableWidgetItem(currentCollegue.CreateDate().toString(currentDate)));
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 3, new QTableWidgetItem("06.05.2017"));
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 4, new QTableWidgetItem(currentCollegue.getFirstName()));
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 5, new QTableWidgetItem(currentCollegue.getLastName()));
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 6, new QTableWidgetItem(currentCollegue.getEmail()));
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 7, new QTableWidgetItem(currentCollegue.getPhone()));
    }
}

void ColleaguesView::SetTableColumnsWidth()
{    
   ui->tblWidgetId->setColumnWidth(0,34);
   ui->tblWidgetId->setColumnWidth(1,329);
   ui->tblWidgetId->setColumnWidth(2,144);
   ui->tblWidgetId->setColumnWidth(3,144);
   ui->tblWidgetId->setColumnWidth(4,150);
   ui->tblWidgetId->setColumnWidth(5,150);
   ui->tblWidgetId->setColumnWidth(6,186);
   ui->tblWidgetId->setColumnWidth(7,134);
}

void ColleaguesView::DoSmthWithObject(int row, int column)
{
    mCurrentCollegue = mColleguesVector.at(row);

}

void ColleaguesView::CreateAddCollegueView()
{
    emit clickedNewLabel();
}




