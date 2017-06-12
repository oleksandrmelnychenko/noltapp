#include "BudgetView.h"
#include "ui_BudgetView.h"

BudgetView::BudgetView(QWidget *parent) :
    QMdiSubWindow(parent,Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::BudgetView)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    SetBudgetHistoryColumnOptions();
    ui->lblIncorrectBudget->setVisible(false);
    ui->lblIncorrectInput->setVisible(false);

    mBudgetService = new BudgetService(this);

    LoadBudget();

    SubscribeToFormEvents();
}

BudgetView::~BudgetView()
{
    delete ui;
}

void BudgetView::SubscribeToFormEvents()
{
    connect(ui->tblBudgetHistory, SIGNAL(cellClicked(int,int)), this, SLOT(WatchCurrentBudgetInformation(int,int)));

    connect(ui->btnSetBudget, SIGNAL(clicked()), this, SLOT(AddBudget()));

    connect(ui->lblBudget, &BudgetLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtBudget);});

    connect(ui->txtBudget, &BudgetLineEdit::inFocus, this,
            [this]{doLabelAnimation(ui->lblBudget, mlblBudgetEndPointY);
            focusIn(ui->txtBudget, ui->lblIncorrectBudget);});

    connect(ui->txtBudget, &BudgetLineEdit::outFocus, this,
            [this]{lostFocusOnLineEdit(ui->txtBudget, ui->lblBudget, mlblBudgetStartPointY, mlblBudgetEndPointY);
            validateLineEditInput(ui->txtBudget, ui->lblIncorrectBudget, mRegBudget, &isBudgetnValid);});
}

void BudgetView::SetBudgetHistoryColumnOptions()
{
    QStringList titleId;
    titleId << "BUDGET DATE" << "TOTAL BUDGET";
    ui->tblBudgetHistory->setColumnCount(3);
    ui->tblBudgetHistory->setColumnHidden(2, true);
    ui->tblBudgetHistory->setHorizontalHeaderLabels(titleId);
    ui->tblBudgetHistory->verticalHeader()->setVisible(false);
    ui->tblBudgetHistory->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tblBudgetHistory->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tblBudgetHistory->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
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
    ui->tblBudgetHistory->setColumnWidth(0,150);
    ui->tblBudgetHistory->setColumnWidth(1,150);
}

void BudgetView::FillBudgetTable(QJsonObject *result)
{
    ui->tblBudgetHistory->clearContents();
    ui->tblBudgetHistory->setRowCount(0);    

    QJsonValue jv = result->value("Body");
    if(jv.isArray())
    {
        QJsonArray ja = jv.toArray();
        for(int i = 0;  i <ja.count(); ++i)
        {
            QJsonObject subtree = ja.at(i).toObject();

            QString currentBudgetId = QString::number(subtree.value("mId").toInt());
            QString currentBudgetAmount = QString::number(subtree.value("mPaymentAmount").toDouble());

            ui->tblBudgetHistory->insertRow(ui->tblBudgetHistory->rowCount());
            ui->tblBudgetHistory->setItem(ui->tblBudgetHistory->rowCount()- 1, 0, new QTableWidgetItem(subtree.value("mPaymentDate").toString()));
            ui->tblBudgetHistory->setItem(ui->tblBudgetHistory->rowCount()- 1, 1, new QTableWidgetItem(currentBudgetAmount));
            ui->tblBudgetHistory->setItem(ui->tblBudgetHistory->rowCount()- 1, 2, new QTableWidgetItem(currentBudgetId));
        }
    }
}

void BudgetView::SetBudgetStatus(QJsonObject *status)
{
    emit setBudgetRequestStatus(status->value("Message").toString());
}

bool BudgetView::isLineEditEmpty(const QLineEdit *lineEdit)
{
    return (QString(lineEdit->text()).isEmpty());
}

void BudgetView::setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY)
{
    isLineEditEmpty(lineEdit) ? mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsStartPointY)
                              : mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsEndPointY);
}

void BudgetView::LoadBudget()
{
    QThread *workerThread = new QThread;
    mBudgetService->moveToThread(workerThread);

    connect(workerThread, SIGNAL(started()), mBudgetService, SLOT(GetBudgetHistory()));
    connect(mBudgetService, SIGNAL(getBudgetHistoryFinished()), workerThread, SLOT(quit()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    connect(mBudgetService, SIGNAL(getBudgetHistory(QJsonObject*)), this, SLOT(FillBudgetTable(QJsonObject*)));
    workerThread->start();
}

void BudgetView::AddBudget()
{
    if(isBudgetnValid && !ui->txtBudget->text().isEmpty())
    {
        ui->btnSetBudget->setEnabled(false);

        mJsonObjectBudget.insert("mPaymentAmount", ui->txtBudget->text());

        SetBudgetStatus(mBudgetService->CreateNewBudget(mJsonObjectBudget));

        ui->btnSetBudget->setEnabled(true);

        LoadBudget();
    }
    else
    {
        ui->lblIncorrectInput->setVisible(true);
    }
}

void BudgetView::WatchCurrentBudgetInformation(int row, int column)
{
    long id = ui->tblBudgetHistory->item(row,2)->text().toLong();
    emit watchCurrentBudgetInformation(id);
}

void BudgetView::setFocusOnLineEdit(QLineEdit *lineEdint)
{
    lineEdint->setFocus();
}

void BudgetView::focusIn(QLineEdit *lineEdit, QLabel *label)
{
    lineEdit->setStyleSheet(mValidateColor);
    label->setVisible(false);
    ui->lblIncorrectInput->setVisible(false);
}

void BudgetView::doLabelAnimation(QLabel *label, int labelsYCoordinate)
{
    mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsYCoordinate);
    ui->widget->hide();
    ui->widget->show();
}

void BudgetView::lostFocusOnLineEdit(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY)
{
    setLabelsPosition(lineEdit, label, labelsStartPointY, labelsEndPointY);
}

void BudgetView::validateLineEditInput(QLineEdit *lineEdit, QLabel *label, QString regPatern, bool *isValid)
{
    QRegExp reg(regPatern);
    bool validate = reg.exactMatch(lineEdit->text());

    if(!validate)
    {
        *isValid = false;
        if(lineEdit->text().isEmpty())
        {
            lineEdit->setStyleSheet(mValidateColor);
        }
        else
        {
            lineEdit->setStyleSheet(mNotValidateColor);
            label->setVisible(true);
        }
    }
    else
    {
        *isValid = true;
        lineEdit->setStyleSheet(mValidateColor);
    }
}
