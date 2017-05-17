#include "SalaryView.h"
#include "ui_SalaryView.h"

#include <QStandardItemModel>
#include <QScrollBar>
#include <QGridLayout>
#include <QDebug>

SalaryView::SalaryView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::SalaryForm)
{
    ui->setupUi(this);
    ui->lblIncorrectSalary->setVisible(false);
    ui->lblIncorrectPayment->setVisible(false);
    ui->lblIncorrectInput->setVisible(false);

    ui->btnPaid->setEnabled(false);
    ui->btnUpdateSalary->setEnabled(false);

    mSalaryService = new SalaryServiece(this);
    mAnimationController = new AnimationController();

    SetColleagueTableColumnOptions();
    SetSalaryHistoryColumnOptions();

    mSalaryService->GetAllColleagues();

    connect(ui->tblWidgetColleagues, SIGNAL(cellClicked(int,int)), this, SLOT(GetColleagueSalaryInformation(int,int)));
    connect(mSalaryService, SIGNAL(getResultsFromRequestColleague(QJsonObject*)), this, SLOT(FillColleagueTable(QJsonObject*)));

    connect(ui->btnUpdateSalary, SIGNAL(clicked()), this, SLOT(UpdateSalary()));
    connect(ui->btnPaid, SIGNAL(clicked(bool)), this, SLOT(PaidSalary()));

    SubscribeToFormEvents();
}

SalaryView::~SalaryView()
{
    delete ui;
}

void SalaryView::GetColleagueSalaryInformation(int row, int column)
{
    long id = ui->tblWidgetColleagues->item(row,2)->text().toLong();

    mCurrentColleagueId = id;

    mSalaryService->GetColleagueById(id);
    connect(mSalaryService, SIGNAL(getResultsFromRequestColleague(QJsonObject*)), this, SLOT(OutputSalary(QJsonObject*)));

//    mSalaryService->GetPaymentHistoryById(id);
//    connect(mSalaryService, SIGNAL(getResultsFromRequestSalary(QJsonObject*)), this, SLOT(OutputPaymentHistory(QJsonObject*)));
}

void SalaryView::OutputSalary(QJsonObject *result)
{
    QJsonValue jv = result->value("Body");
    QJsonObject subtree = jv.toObject();

    mJsonObjectColleague = subtree;

    QString salary = QString::number(subtree.value("mSalaryAmount").toDouble());

    ui->txtSalary->setText(salary);
    ui->txtPaid->setText(salary);

    setLabelsPosition(ui->txtSalary, ui->lblSalary, mlblSalaryStartPointY, mlblSalaryEndPointY);
    setLabelsPosition(ui->txtPaid, ui->lblToPay, mlblPaymentStartPointY, mlblPaymentEndPointY);

    ui->btnPaid->setEnabled(true);
    ui->btnUpdateSalary->setEnabled(true);

    ui->widget->hide();
    ui->widget->show();
}

void SalaryView::UpdateSalary()
{
    if(isSalaryValid && !ui->txtSalary->text().isEmpty())
    {
        mJsonObjectColleague.insert("mSalaryAmount", ui->txtSalary->text());

        mSalaryService->UpdateColleague(mJsonObjectColleague);

        ui->btnUpdateSalary->setEnabled(false);

        connect(mSalaryService, SIGNAL(getResultsFromRequestSalary(QJsonObject*)), this, SLOT(UpdateColleagueRequestStatus(QJsonObject*)));
    }
    else
    {
        ui->lblIncorrectInput->setText("Incorrect salary amount");
        ui->lblIncorrectInput->setVisible(true);
    }
}

void SalaryView::PaidSalary()
{
    mJsonObjectSalary.insert("mPaymentAmount", ui->txtPaid->text());

    mSalaryService->PaidSalary(mCurrentColleagueId, mJsonObjectSalary);

    connect(mSalaryService, SIGNAL(getResultsFromRequestSalary(QJsonObject*)), this, SLOT(OutputPaymentHistory(QJsonObject*)));
}

void SalaryView::OutputPaymentHistory(QJsonObject *result)
{
    QJsonValue jv = result->value("Body");
    if(jv.isArray())
    {
        QJsonArray ja = jv.toArray();
        for(int i = 0;  i <ja.count(); ++i)
        {
            QJsonObject subtree = ja.at(i).toObject();

            ui->tblWidgetSalaryHistory->insertRow(ui->tblWidgetSalaryHistory->rowCount());
            ui->tblWidgetSalaryHistory->setItem(ui->tblWidgetSalaryHistory->rowCount()- 1, 0, new QTableWidgetItem(subtree.value("mPaymentDate").toString()));
            ui->tblWidgetSalaryHistory->setItem(ui->tblWidgetSalaryHistory->rowCount()- 1, 1, new QTableWidgetItem(subtree.value("mPaymentAmount").toString()));
        }
    }
}

void SalaryView::SubscribeToFormEvents()
{
    connect(ui->lblSalary, &SalaryLabel::pressIn, this , [this]{setFocusOnLineEdit(ui->txtSalary);});
    connect(ui->lblToPay, &SalaryLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtPaid);});

    connect(ui->txtSalary, &SalaryLineEdit::inFocus, this,
            [this]{doLabelAnimation(ui->lblSalary, mlblSalaryEndPointY);
            focusIn(ui->txtSalary, ui->lblIncorrectSalary);});
    connect(ui->txtPaid, &SalaryLineEdit::inFocus, this,
            [this]{doLabelAnimation(ui->lblToPay, mlblPaymentEndPointY);
            focusIn(ui->txtPaid, ui->lblIncorrectPayment);});

    connect(ui->txtSalary, &SalaryLineEdit::outFocus, this,
            [this]{lostFocusOnLineEditSalary();
            validateLineEditInput(ui->txtSalary, ui->lblIncorrectSalary, mRegSalary, &isSalaryValid);});
    connect(ui->txtPaid, &SalaryLineEdit::outFocus, this,
            [this]{lostFocusOnLineEditPayment();
        validateLineEditInput(ui->txtPaid, ui->lblIncorrectPayment, mRegPayment, &isPaymentValid);});
}

void SalaryView::LoadColleaguePaymentHistory(long id)
{
    mSalaryService->GetPaymentHistoryById(id);
    connect(mSalaryService, SIGNAL(getResultsFromRequestSalary(QJsonObject*)), this, SLOT(OutputPaymentHistory(QJsonObject*)));
}

QString SalaryView::getInformationFromLineEdit(QLineEdit *lineEdit)
{
    return lineEdit->text();
}

void SalaryView::clearFocusOfLineEdits()
{
    ui->txtSalary->clearFocus();
    ui->txtPaid->clearFocus();
}

bool SalaryView::isLineEditEmpty(const QLineEdit *lineEdit)
{
    return (QString(lineEdit->text()).isEmpty());
}

void SalaryView::setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY)
{
    isLineEditEmpty(lineEdit) ? mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsStartPointY)
                              : mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsEndPointY);
}

void SalaryView::SetColleagueTableColumnOptions()
{
    QStringList titleId;
    titleId <<"FIRST NAME" << "LAST NAME";
    ui->tblWidgetColleagues->setColumnCount(3);
    ui->tblWidgetColleagues->setColumnHidden(2, true);
    ui->tblWidgetColleagues->setHorizontalHeaderLabels(titleId);
    ui->tblWidgetColleagues->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tblWidgetColleagues->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tblWidgetColleagues->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
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
    ui->tblWidgetColleagues->setColumnWidth(0,150);
    ui->tblWidgetColleagues->setColumnWidth(1,150);
}

void SalaryView::SetSalaryHistoryColumnOptions()
{
    QStringList titleId;
    titleId <<"PAYMENT DATE" << "PAYMENT";
    ui->tblWidgetSalaryHistory->setColumnCount(3);
    ui->tblWidgetSalaryHistory->setColumnHidden(2, true);
    ui->tblWidgetSalaryHistory->setHorizontalHeaderLabels(titleId);
    ui->tblWidgetSalaryHistory->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tblWidgetSalaryHistory->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tblWidgetSalaryHistory->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
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
    ui->tblWidgetSalaryHistory->setColumnWidth(0,170);
    ui->tblWidgetSalaryHistory->setColumnWidth(1,130);
}

void SalaryView::FillColleagueTable(QJsonObject *result)
{
    QJsonValue jv = result->value("Body");
    if(jv.isArray())
    {
        QJsonArray ja = jv.toArray();
        for(int i = 0;  i <ja.count(); ++i)
        {
            QJsonObject subtree = ja.at(i).toObject();

            QString currentCollegueId = QString::number(subtree.value("mId").toInt());

            ui->tblWidgetColleagues->insertRow(ui->tblWidgetColleagues->rowCount());
            ui->tblWidgetColleagues->setItem(ui->tblWidgetColleagues->rowCount()- 1, 0, new QTableWidgetItem(subtree.value("mFirstName").toString()));
            ui->tblWidgetColleagues->setItem(ui->tblWidgetColleagues->rowCount()- 1, 1, new QTableWidgetItem(subtree.value("mLastName").toString()));
            ui->tblWidgetColleagues->setItem(ui->tblWidgetColleagues->rowCount()- 1, 2, new QTableWidgetItem(currentCollegueId));
        }
    }
}

void SalaryView::RequestStatus(QJsonObject *status)
{
    emit requestStatus(status->value("Message").toString());
}

void SalaryView::UpdateColleagueRequestStatus(QJsonObject *status)
{
    emit updateColleagueRequestStatus(status->value("Message").toString());
    ui->btnUpdateSalary->setEnabled(true);
}

void SalaryView::focusIn(QLineEdit *lineEdit, QLabel *label)
{
    lineEdit->setStyleSheet(mValidateColor);
    label->setVisible(false);
    ui->lblIncorrectInput->setVisible(false);
}

void SalaryView::validateLineEditInput(QLineEdit *lineEdit, QLabel *label, QString regPatern, bool *isValid)
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

void SalaryView::setFocusOnLineEdit(QLineEdit *lineEdint)
{
    lineEdint->setFocus();
}

void SalaryView::doLabelAnimation(QLabel *label, int labelsYCoordinate)
{
    mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsYCoordinate);
    ui->widget->hide();
    ui->widget->show();
}

void SalaryView::lostFocusOnLineEditSalary()
{
    setLabelsPosition(ui->txtSalary, ui->lblSalary, mlblSalaryStartPointY, mlblSalaryEndPointY);
}

void SalaryView::lostFocusOnLineEditPayment()
{
    setLabelsPosition(ui->txtPaid, ui->lblToPay, mlblPaymentStartPointY, mlblPaymentEndPointY);
}
