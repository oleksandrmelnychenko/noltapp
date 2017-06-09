#include "CurrentBudgetInformationView.h"
#include "ui_CurrentBudgetInformationView.h"

CurrentBudgetInformationView::CurrentBudgetInformationView(QWidget *parent, long id) :
    QMdiSubWindow(parent,  Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::CurrentBudgetInformationView),
    mId(id)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    SetTableColumnOptions();

    mBudgetService = new BudgetService(this);

    FillCurrentBudgetTable(mBudgetService->GetBudgetById(mId));
}

CurrentBudgetInformationView::~CurrentBudgetInformationView()
{
    delete ui;
}

void CurrentBudgetInformationView::SetTableColumnOptions()
{
    QStringList titleId;
    titleId << "DATE" << "DESCRIPTION" << "AMMOUNT";
    ui->tblCurrentBudgetHistory->setColumnCount(3);
    ui->tblCurrentBudgetHistory->setHorizontalHeaderLabels(titleId);
    ui->tblCurrentBudgetHistory->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tblCurrentBudgetHistory->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tblCurrentBudgetHistory->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
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
    ui->tblCurrentBudgetHistory->setColumnWidth(0,100);
    ui->tblCurrentBudgetHistory->setColumnWidth(1,250);
    ui->tblCurrentBudgetHistory->setColumnWidth(2,100);
}

void CurrentBudgetInformationView::FillCurrentRow(QJsonObject *subtree, BudgetType budgetType)
{
    QJsonValue jvSalary = subtree->value("ColleagueSalary");
    QJsonObject currentSalaryObject = jvSalary.toObject();
    QJsonValue jvSalaySubtree = currentSalaryObject.value("mColleague");
    QJsonObject currentColleagueSalaryObject = jvSalaySubtree.toObject();

    QJsonValue jvExpenses = subtree->value("OtherExpenses");
    QJsonObject currentExpansesObject = jvExpenses.toObject();

    QString description;
    QString payment = QString::number(subtree->value("mPaymentAmount").toDouble());

    switch (budgetType) {
    case BudgetType::Budget:
        description = "Budget income";
        break;

    case BudgetType::Salary:
        description = "Salary: " + currentColleagueSalaryObject.value("mFirstName").toString()
                + " " + currentColleagueSalaryObject.value("mLastName").toString();
        break;

    case BudgetType::OtherExpense:
        description = "Office: " + currentExpansesObject.value("mDescription").toString();
        break;

    default:
        description = "##########";
        break;
    }

    ui->tblCurrentBudgetHistory->setItem(ui->tblCurrentBudgetHistory->rowCount()- 1, 0, new QTableWidgetItem(subtree->value("mPaymentDate").toString()));
    ui->tblCurrentBudgetHistory->setItem(ui->tblCurrentBudgetHistory->rowCount()- 1, 1, new QTableWidgetItem(description));
    ui->tblCurrentBudgetHistory->setItem(ui->tblCurrentBudgetHistory->rowCount()- 1, 2, new QTableWidgetItem(payment));
}

void CurrentBudgetInformationView::FillCurrentBudgetTable(QJsonObject *result)
{

    QJsonValue jv = result->value("Body");
    QJsonObject subtree = jv.toObject();

    double currentBudget = subtree.value("mPaymentAmount").toDouble();

    QString totalBudget = QString::number(subtree.value("mPaymentAmount").toDouble());
    ui->lblTotalBudget->setText(totalBudget);


    QJsonValue jvBudgetHistory = subtree.value("BudgetHistory");
    if(jvBudgetHistory.isArray())
    {
        QJsonArray ja = jvBudgetHistory.toArray();
        for(int i = 0;  i <ja.count(); ++i)
        {
            QJsonObject subtree = ja.at(i).toObject();

            ui->tblCurrentBudgetHistory->insertRow(ui->tblCurrentBudgetHistory->rowCount());

            if(!subtree.value("Budget").isNull())
            {
                FillCurrentRow(&subtree, BudgetType::Budget);
            }
            if(!subtree.value("ColleagueSalary").isNull())
            {
                currentBudget -= subtree.value("mPaymentAmount").toDouble();
                FillCurrentRow(&subtree, BudgetType::Salary);
            }
            if(!subtree.value("OtherExpenses").isNull())
            {
                currentBudget -= subtree.value("mPaymentAmount").toDouble();
                FillCurrentRow(&subtree, BudgetType::OtherExpense);
            }
        }
    }
    ui->lblCurrentBudget->setText(QString::number(currentBudget));
}
