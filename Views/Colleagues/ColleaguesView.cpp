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
    mRepository = new ColleagueOperationRepository(this);
    mRepository->GetAllColleagues();

    SetTableColumnOptions();

    connect(ui->tblWidgetId,  SIGNAL(cellClicked(int,int)), this, SLOT(UpdateCurrentCollegues(int, int)));
    connect(ui->lblAddNew, SIGNAL(pressIn()), this, SLOT(CreateAddCollegueView()));

    connect(mRepository, SIGNAL(getResultsFromRequest(QJsonObject*)), this, SLOT(ResultFromRequest(QJsonObject*)));
}

ColleaguesView::~ColleaguesView()
{
    delete ui;
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

void ColleaguesView::SetTableColumnOptions()
{
    QStringList titleId;
    titleId << "ID" << "FIRST NAME" << "LAST NAME" << "EMAIL" << "PHONE" << "CREATE DATE" << "UPDATE DATE" ;
    ui->tblWidgetId->setColumnCount(7);
    ui->tblWidgetId->setHorizontalHeaderLabels(titleId);
    ui->tblWidgetId->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    SetTableColumnsWidth();
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

void ColleaguesView::ResultFromRequest(QJsonObject *result)
{
    QJsonValue jv = result->value("Body");
    if(jv.isArray())
    {
        QJsonArray ja = jv.toArray();
        for(int i = 0;  i <ja.count(); ++i)
        {
            QJsonObject subtree = ja.at(i).toObject();

            QString currentCollegueId = QString::number(subtree.value("mId").toInt());

            ui->tblWidgetId->insertRow(ui->tblWidgetId->rowCount());
            ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 0, new QTableWidgetItem(currentCollegueId));
            ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 1, new QTableWidgetItem(subtree.value("mFirstName").toString()));
            ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 2, new QTableWidgetItem(subtree.value("mLastName").toString()));
            ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 3, new QTableWidgetItem(subtree.value("mEmail").toString()));
            ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 4, new QTableWidgetItem(subtree.value("mPhone").toString()));
            ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 5, new QTableWidgetItem(subtree.value("mCreateDate").toString()));
            ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 6, new QTableWidgetItem(subtree.value("mUpdateDate").toString()));
        }
    }
}
