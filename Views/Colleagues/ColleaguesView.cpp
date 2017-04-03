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
    titleId << "Id:";
    ui->tblWidgetId->setColumnCount(1);
    ui->tblWidgetId->setHorizontalHeaderLabels(titleId);

    connect(ui->btnLoadData, SIGNAL(clicked(bool)), SLOT(LoadData()));
    connect(ui->tblWidgetId,  SIGNAL(cellClicked(int,int)), this, SLOT(DoSmthWithObject(int, int)));
    connect(ui->btnAddCollegue, SIGNAL(clicked(bool)), this, SLOT(CreateAddCollegueView()));

    QDate d(2017,3,4);
    PersonEntity bob(1,"bob123", d, "Bob", "Arum", "bob@gmail.com", "097554822");
    PersonEntity jack(2,"jack123", d, "Jack", "Partak", "partak@gmail.com", "0967324234");
    PersonEntity rachel(3,"rachel123", d, "Rachel", "Valera", "rv@gmail.com", "0775464523");
    PersonEntity korky(4,"korky123", d, "Korky", "Melloun", "korky@gmail.com", "097544962");
    PersonEntity jose(5,"jose123", d, "Jose", "Mour", "jm@gmail.com", "097678912");

    mColleguesVector << bob << jack << rachel << korky << jose;
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

        ui->tblWidgetId->insertRow(ui->tblWidgetId->rowCount());
        ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 0, new QTableWidgetItem(currentCollegueId));
    }
}

void ColleaguesView::DoSmthWithObject(int row, int column)
{
    mCurrentCollegue = mColleguesVector.at(row);

    ui->txtEditNetUiId->setText(mCurrentCollegue.NetUiID().toString());
    ui->txtEditCreateDate->setText(mCurrentCollegue.CreateDate().toString());
    ui->txtEditFirstName->setText(mCurrentCollegue.getFirstName());
    ui->txtEditLastName->setText(mCurrentCollegue.getLastName());
    ui->txtEditEmail->setText(mCurrentCollegue.getEmail());
    ui->txtEditPhone->setText(mCurrentCollegue.getPhone());
}

void ColleaguesView::CreateAddCollegueView()
{
    emit clickedAddCollegueButton();    
}




