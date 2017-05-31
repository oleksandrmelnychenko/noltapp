#include "BudgetView.h"
#include "ui_BudgetView.h"

BudgetView::BudgetView(QWidget *parent) :
    QMdiSubWindow(parent,Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::BudgetView)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->lblIncorrectBudget->setVisible(false);



    SubscribeToFormEvents();
}

BudgetView::~BudgetView()
{
    delete ui;
}

void BudgetView::SubscribeToFormEvents()
{
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
    titleId << "BUDGET DATE" << "BUDGET";
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
    ui->tblBudgetHistory->setColumnWidth(0,130);
    ui->tblBudgetHistory->setColumnWidth(1,170);
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

void BudgetView::AddBudget()
{

}

void BudgetView::setFocusOnLineEdit(QLineEdit *lineEdint)
{
    lineEdint->setFocus();
}

void BudgetView::focusIn(QLineEdit *lineEdit, QLabel *label)
{
    lineEdit->setStyleSheet(mValidateColor);
    label->setVisible(false);
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
