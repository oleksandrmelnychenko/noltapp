#include "ColleaguesView.h"
#include "ui_ColleaguesView.h"

#include <QDebug>
#include <QStandardItemModel>

ColleaguesView::ColleaguesView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::ColleaguesForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    QStringList titleId;
    titleId << "ID" << "FIRST NAME" << "LAST NAME" << "EMAIL" << "PHONE" << "CREATE DATE" << "UPDATE DATE" ;
    ui->tblWidgetId->setColumnCount(7);
    ui->tblWidgetId->setHorizontalHeaderLabels(titleId);    
    ui->tblWidgetId->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);    

    connect(ui->tblWidgetId,  SIGNAL(cellClicked(int,int)), this, SLOT(UpdateCurrentCollegues(int, int)));
    connect(ui->lblAddNew, SIGNAL(pressIn()), this, SLOT(CreateAddCollegueView()));    

    QDate d = QDate::currentDate();
    PersonEntity bob(11,"netUiId", d, "Bob", "Arum", "bob@gmail.com", "097554822");
    PersonEntity jack(42,"netUiId", d, "Jack", "Partak", "partak@gmail.com", "0967324234");
    PersonEntity rachel(53, "netUiId", d, "Rachel", "Valera", "rv@gmail.com", "0775464523");
    PersonEntity korky(47, "netUiId", d, "Korky", "Melloun", "korky@gmail.com", "097544962");
    PersonEntity jose(85, "netUiId", d, "Jose", "Mour", "jm@gmail.com", "097678912");

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
        //ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 5, new QTableWidgetItem(currentCollegue.CreateDate().toString(currentDate)));
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 6, new QTableWidgetItem("06.05.2017"));
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 1, new QTableWidgetItem(currentCollegue.getFirstName()));
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 2, new QTableWidgetItem(currentCollegue.getLastName()));
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 3, new QTableWidgetItem(currentCollegue.getEmail()));
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 4, new QTableWidgetItem(currentCollegue.getPhone()));
    }
}

void ColleaguesView::SetTableColumnsWidth()
{    
   ui->tblWidgetId->setColumnWidth(0,40);
   ui->tblWidgetId->setColumnWidth(1,250);
   ui->tblWidgetId->setColumnWidth(2,250);
   ui->tblWidgetId->setColumnWidth(3,280);
   ui->tblWidgetId->setColumnWidth(4,160);
   ui->tblWidgetId->setColumnWidth(5,145);
   ui->tblWidgetId->setColumnWidth(6,145);
}

void ColleaguesView::CreateAddCollegueView()
{
    emit clickedNewLabel();
}

void ColleaguesView::UpdateCurrentCollegues(int row, int column)
{
    long id = ui->tblWidgetId->item(row,0)->text().toLong();
    emit updateCurrentCollegues(id);    
}
