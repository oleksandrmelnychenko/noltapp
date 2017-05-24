#include "ColleaguesView.h"
#include "ui_ColleaguesView.h"

#include <QDebug>
#include <QStandardItemModel>
#include <QScrollBar>
#include <QGridLayout>
#include <QThread>


ColleaguesView::ColleaguesView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::ColleaguesForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    SetTableColumnOptions();

    mColleagueService = new ColleagueService(this);
    //
    //QThread *workerThread = new QThread(this);
    //mColleagueService->moveToThread(workerThread);
    //
    OutputColleagues(mColleagueService->GetAllColleagues()); // change fucntion
    //workerThread->start();

    connect(ui->tblWidgetId,  SIGNAL(cellClicked(int,int)), this, SLOT(UpdateCurrentCollegues(int, int)));
    connect(ui->lblAddNew, SIGNAL(pressIn()), this, SLOT(CreateAddCollegueView()));    
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
   ui->tblWidgetId->setColumnWidth(4,130);
   ui->tblWidgetId->setColumnWidth(5,106);
   ui->tblWidgetId->setColumnWidth(6,106);
   ui->tblWidgetId->setColumnWidth(7,106);
}

void ColleaguesView::SetTableColumnOptions()
{
    QStringList titleId;
    titleId << "ID" << "FIRST NAME" << "LAST NAME" << "EMAIL" << "PHONE" << "BIRTHDAY" << "CREATE DATE" << "UPDATE DATE" ;
    ui->tblWidgetId->setColumnCount(8);
    ui->tblWidgetId->setHorizontalHeaderLabels(titleId);
    ui->tblWidgetId->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tblWidgetId->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  
    ui->tblWidgetId->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                                        "    border: 1px solid #797979;"
                                                        "    background:#ffffff;;"
                                                        "    width:3px;    "
                                                        "    margin: 0px 0px 0px 0px;"
                                                        "}"
                                                        "QScrollBar::handle:vertical {"
                                                        "    background: #797979;"   // #18181a; #797979; #909090
                                                        "    min-height: 0px;"
                                                        "}"
                                                        "QScrollBar::add-line:vertical {"
                                                        "    height: 0px;"
                                                        "}"
                                                        "QScrollBar::sub-line:vertical {"
                                                        "    height: 0 px;"
                                                        "}");

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

void ColleaguesView::OutputColleagues(QJsonObject *result)
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
            ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 5, new QTableWidgetItem(subtree.value("mDateOfBirth").toString()));
            ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 6, new QTableWidgetItem(subtree.value("mCreateDate").toString()));
            ui->tblWidgetId->setItem(ui->tblWidgetId->rowCount()- 1, 7, new QTableWidgetItem(subtree.value("mUpdateDate").toString()));
        }
    }
}
