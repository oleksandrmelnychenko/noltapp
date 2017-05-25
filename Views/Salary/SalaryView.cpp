#include "SalaryView.h"
#include "ui_SalaryView.h"

SalaryView::SalaryView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::SalaryForm)
{
    ui->setupUi(this);    
    SetUiElementsOptions();

    mSalaryService = new SalaryServiece(this);
    mAnimationController = new AnimationController();

    FillColleagueTable(mSalaryService->GetAllColleagues());

    SubscribeToFormEvents();
}

SalaryView::~SalaryView()
{
    delete ui;
}

void SalaryView::SetUiElementsOptions()
{
    ui->lblIncorrectSalary->setVisible(false);
    ui->lblIncorrectPayment->setVisible(false);
    ui->lblIncorrectInput->setVisible(false);

    ui->btnPaid->setEnabled(false);
    ui->btnUpdateSalary->setEnabled(false);

    SetColleagueTableColumnOptions();
    SetSalaryHistoryColumnOptions();
}

void SalaryView::GetColleagueSalaryInformation(int row, int column)
{
    long id = ui->tblWidgetColleagues->item(row,1)->text().toLong();

    mCurrentColleagueId = id;

    OutputSalary(mSalaryService->GetColleagueById(id));
    OutputPaymentHistory(mSalaryService->GetPaymentHistoryById(id));
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
}

void SalaryView::UpdateSalary()
{
    if(isSalaryValid && !ui->txtSalary->text().isEmpty())
    {
        ui->btnUpdateSalary->setEnabled(false);

        mJsonObjectColleague.insert("mSalaryAmount", ui->txtSalary->text());
        ui->txtPaid->setText(ui->txtSalary->text());

        UpdateColleagueSalaryRequestStatus(mSalaryService->UpdateColleagueSalary(mJsonObjectColleague));

        ui->btnUpdateSalary->setEnabled(true);
    }
    else
    {
        ui->lblIncorrectInput->setText("Incorrect salary amount");
        ui->lblIncorrectInput->setVisible(true);
    }
}

void SalaryView::PaidSalary()
{
    if(isPaymentValid && !ui->txtPaid->text().isEmpty())
    {
        ui->btnPaid->setEnabled(false);

        mJsonObjectSalary.insert("mPaymentAmount", ui->txtPaid->text());

        PaidSalaryRequestStatus(mSalaryService->PaidSalary(mCurrentColleagueId, mJsonObjectSalary));

        ui->btnPaid->setEnabled(true);

        OutputPaymentHistory(mSalaryService->GetPaymentHistoryById(mCurrentColleagueId));
    }
    else
    {
        ui->lblIncorrectInput->setText("Incorrect payment amount");
        ui->lblIncorrectInput->setVisible(true);
    }
}

void SalaryView::OutputPaymentHistory(QJsonObject *result)
{
    ui->tblWidgetSalaryHistory->clearContents();
    ui->tblWidgetSalaryHistory->setRowCount(0);

    QJsonValue jv = result->value("Body");

    if(jv.isArray())
    {
        QJsonArray ja = jv.toArray();
        for(int i = 0;  i <ja.count(); ++i)
        {
            QJsonObject subtree = ja.at(i).toObject();

            QString payment = QString::number(subtree.value("mPaymentAmount").toDouble());

            ui->tblWidgetSalaryHistory->insertRow(ui->tblWidgetSalaryHistory->rowCount());
            ui->tblWidgetSalaryHistory->setItem(ui->tblWidgetSalaryHistory->rowCount()- 1, 0, new QTableWidgetItem(subtree.value("mPaymentDate").toString()));
            ui->tblWidgetSalaryHistory->setItem(ui->tblWidgetSalaryHistory->rowCount()- 1, 1, new QTableWidgetItem(payment));
        }
    }
}

void SalaryView::SubscribeToFormEvents()
{
    connect(ui->tblWidgetColleagues, SIGNAL(cellClicked(int,int)), this, SLOT(GetColleagueSalaryInformation(int,int)));

    connect(ui->btnUpdateSalary, SIGNAL(clicked()), this, SLOT(UpdateSalary()));
    connect(ui->btnPaid, SIGNAL(clicked(bool)), this, SLOT(PaidSalary()));

    connect(ui->lblSalary, &SalaryLabel::pressIn, this , [this]{setFocusOnLineEdit(ui->txtSalary);});
    connect(ui->lblToPay, &SalaryLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtPaid);});

    connect(ui->txtSalary, &SalaryLineEdit::inFocus, this,
            [this]{doLabelAnimation(ui->lblSalary, mlblSalaryEndPointY);
            focusIn(ui->txtSalary, ui->lblIncorrectSalary);});
    connect(ui->txtPaid, &SalaryLineEdit::inFocus, this,
            [this]{doLabelAnimation(ui->lblToPay, mlblPaymentEndPointY);
            focusIn(ui->txtPaid, ui->lblIncorrectPayment);});

    connect(ui->txtSalary, &SalaryLineEdit::outFocus, this,
            [this]{lostFocusOnLineEdit(ui->txtSalary, ui->lblSalary, mlblSalaryStartPointY, mlblSalaryEndPointY);
            validateLineEditInput(ui->txtSalary, ui->lblIncorrectSalary, mRegSalary, &isSalaryValid);});
    connect(ui->txtPaid, &SalaryLineEdit::outFocus, this,
            [this]{lostFocusOnLineEdit(ui->txtPaid, ui->lblToPay, mlblPaymentStartPointY, mlblPaymentEndPointY);
            validateLineEditInput(ui->txtPaid, ui->lblIncorrectPayment, mRegPayment, &isPaymentValid);});
}

void SalaryView::LoadColleaguePaymentHistory(long id)
{
    mSalaryService->GetPaymentHistoryById(id);    
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
    titleId <<"COLLEAGUES";
    ui->tblWidgetColleagues->setColumnCount(2);
    ui->tblWidgetColleagues->setColumnHidden(1, true);
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
    ui->tblWidgetColleagues->setColumnWidth(0,300);   ;
}

void SalaryView::SetSalaryHistoryColumnOptions()
{
    QStringList titleId;
    titleId <<"PAYMENT DATE" << "PAYMENT";
    ui->tblWidgetSalaryHistory->setColumnCount(3);
    ui->tblWidgetSalaryHistory->setColumnHidden(2, true);
    ui->tblWidgetSalaryHistory->setHorizontalHeaderLabels(titleId);
    ui->tblWidgetSalaryHistory->verticalHeader()->setVisible(false);
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
            QString colleague = subtree.value("mFirstName").toString()+ " " + subtree.value("mLastName").toString();

            ui->tblWidgetColleagues->insertRow(ui->tblWidgetColleagues->rowCount());
            ui->tblWidgetColleagues->setItem(ui->tblWidgetColleagues->rowCount()- 1, 0, new QTableWidgetItem(colleague));
            ui->tblWidgetColleagues->setItem(ui->tblWidgetColleagues->rowCount()- 1, 1, new QTableWidgetItem(currentCollegueId));
        }
    }
}

void SalaryView::PaidSalaryRequestStatus(QJsonObject *status)
{
    emit paidSalaryRequestStatus(status->value("Message").toString());
}

void SalaryView::UpdateColleagueSalaryRequestStatus(QJsonObject *status)
{
    emit updateColleagueSalaryRequestStatus(status->value("Message").toString());
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
}

void SalaryView::lostFocusOnLineEdit(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY)
{
    setLabelsPosition(lineEdit, label, labelsStartPointY, labelsEndPointY);
}
