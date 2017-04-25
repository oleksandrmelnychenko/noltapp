#include "UpdateCollegueView.h"
#include "ui_UpdateCollegueView.h"

UpdateCollegueView::UpdateCollegueView(QWidget *parent,long id) :
    QMdiSubWindow(parent, Qt::FramelessWindowHint | Qt::Window),
    ui(new Ui::UpdateCollegueView),
    mIdUpdatedCollegue(id)
{
    ui->setupUi(this);

    mRepository = new ColleagueOperationRepository(this);
    mRepository->GetColleagueById(id);

    connect(mRepository, SIGNAL(getResultsFromRequest(QJsonObject*)), this, SLOT(ResultFromRequest(QJsonObject*)));
}

UpdateCollegueView::~UpdateCollegueView()
{
    delete ui;
}

void UpdateCollegueView::ResultFromRequest(QJsonObject *result)
{
    QJsonValue jv = result->value("Body");
    QJsonObject subtree = jv.toObject();

    ui->txtEditFirstName->setText( subtree.value("mFirstName").toString());
    ui->txtEditLastName->setText(subtree.value("mLastName").toString());
    ui->txtEditEmail->setText(subtree.value("mEmail").toString());
    ui->txtEditPhone->setText(subtree.value("mPhone").toString());
}
