#include "SalaryView.h"
#include "ui_SalaryView.h"

SalaryView::SalaryView(QWidget *parent) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::SalaryForm)
{
    ui->setupUi(this);
    ui->lblIncorrectSalary->setVisible(false);
    ui->lblIncorrectPayment->setVisible(false);

    mRepository = new ColleagueOperationRepository(this);
    mAnimationController = new AnimationController();

    SubscribeToFormEvents();
}

SalaryView::~SalaryView()
{
    delete ui;
}

void SalaryView::SubscribeToFormEvents()
{

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

void SalaryView::RequestStatus(QJsonObject *status)
{
    emit requestStatus(status->value("Message").toString());
}

void SalaryView::focusIn(QLineEdit *lineEdit, QLabel *label)
{
    lineEdit->setStyleSheet(mValidateColor);
    label->setVisible(false);
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
