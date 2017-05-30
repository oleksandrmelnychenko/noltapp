#include "OfficeView.h"
#include "ui_OfficeView.h"

OfficeView::OfficeView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::OfficeForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    SetPaymentHistoryColumnOptions();

    ui->lblIncorrectPayment->setVisible(false);
    ui->lblIncorrectDescription->setVisible(false);

    SubscribeToFormEvents();
}

OfficeView::~OfficeView()
{
    delete ui;
}

void OfficeView::SubscribeToFormEvents()
{    
    connect(ui->btnPaid, SIGNAL(clicked(bool)), this, SLOT(PaidSalary()));

    connect(ui->lblToPay, &OfficeLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtToPay);});
    connect(ui->lblDescription, &OfficeLabel::pressIn, this, [this]{setFocusOnLineEdit(ui->txtDescription);});

    connect(ui->txtToPay, &OfficeLineEdit::inFocus, this,
            [this]{doLabelAnimation(ui->lblToPay, mlblPaymentEndPointY);
            focusIn(ui->txtToPay, ui->lblIncorrectPayment);});
    connect(ui->txtDescription, &OfficeLineEdit::inFocus, this,
            [this]{doLabelAnimation(ui->lblDescription, mlblDescriptionEndPointY);
            focusIn(ui->txtDescription, ui->lblIncorrectDescription);});

    connect(ui->txtToPay, &OfficeLineEdit::outFocus, this,
            [this]{lostFocusOnLineEdit(ui->txtToPay, ui->lblToPay, mlblPaymentStartPointY, mlblPaymentEndPointY);
            validateLineEditInput(ui->txtToPay, ui->lblIncorrectPayment, mRegPayment, &isPaymentValid);});
    connect(ui->txtDescription, &OfficeLineEdit::outFocus, this,
            [this]{lostFocusOnLineEdit(ui->txtDescription, ui->lblDescription, mlblDescriptionStartPointY, mlblDescriptionEndPointY);
            validateLineEditInput(ui->txtDescription, ui->lblIncorrectDescription, mRegDescription, &isDescriptionValid);});
}

void OfficeView::SetPaymentHistoryColumnOptions()
{
    QStringList titleId;
    titleId << "PAYMENT DATE" << "DESCRIPTION" << "PAYMENT";
    ui->tblWidgetSalaryHistory->setColumnCount(4);
    ui->tblWidgetSalaryHistory->setColumnHidden(3, true);
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
    ui->tblWidgetSalaryHistory->setColumnWidth(0,130);
    ui->tblWidgetSalaryHistory->setColumnWidth(1,200);
    ui->tblWidgetSalaryHistory->setColumnWidth(2,120);

}

bool OfficeView::isLineEditEmpty(const QLineEdit *lineEdit)
{
    return (QString(lineEdit->text()).isEmpty());
}

void OfficeView::setLabelsPosition(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY)
{
    isLineEditEmpty(lineEdit) ? mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsStartPointY)
                              : mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsEndPointY);
}

void OfficeView::PaidSalary()
{

}

void OfficeView::setFocusOnLineEdit(QLineEdit *lineEdint)
{
    lineEdint->setFocus();
}

void OfficeView::focusIn(QLineEdit *lineEdit, QLabel *label)
{
    lineEdit->setStyleSheet(mValidateColor);
    label->setVisible(false);    
}

void OfficeView::doLabelAnimation(QLabel *label, int labelsYCoordinate)
{
    mAnimationController->labelAnimationByY(label, mAnimationDuration, labelsYCoordinate);
    ui->widget->hide();
    ui->widget->show();
}

void OfficeView::lostFocusOnLineEdit(const QLineEdit *lineEdit, QLabel *label, int labelsStartPointY, int labelsEndPointY)
{
    setLabelsPosition(lineEdit, label, labelsStartPointY, labelsEndPointY);
}

void OfficeView::validateLineEditInput(QLineEdit *lineEdit, QLabel *label, QString regPatern, bool *isValid)
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
