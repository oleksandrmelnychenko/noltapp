#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::createColleaguesForm()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mColleaguesForm = new ColleaguesForm(ui->mdiArea);
    mColleaguesForm->setGeometry(10,40,640,440);
    mColleaguesForm->show();
    mCurrentMdiSubForm = mColleaguesForm;
}

void MainWindow::createOfficeForm()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mOfficeForm = new OfficeForm(ui->mdiArea);
    mOfficeForm->setGeometry(10,40,640,440);
    mOfficeForm->show();
    mCurrentMdiSubForm = mOfficeForm;
}

void MainWindow::createSalaryForm()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mSalaryForm = new SalaryForm(ui->mdiArea);
    mSalaryForm->setGeometry(10,40,640,440);
    mSalaryForm->show();
    mCurrentMdiSubForm = mSalaryForm;
}

void MainWindow::deleteMdiSubForm(QMdiSubWindow *form)
{
    if(form != nullptr)
    {
        if(form == mColleaguesForm)
        {
            delete mColleaguesForm;
            mColleaguesForm = nullptr;
            qDebug() << "Delete Collegues";
        }
        else if(form == mSalaryForm)
        {
            delete mSalaryForm;
            mSalaryForm = nullptr;
            qDebug() << "Delete Salary";
        }
        else if(form == mOfficeForm)
        {
            delete mOfficeForm;
            mOfficeForm = nullptr;
            qDebug() << "Delete Office";
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createColleaguesForm();
    //mCurrentMdiSubForm->setGeometry(0,0,640,440);

    connect(ui->btnColleagues, SIGNAL(clicked()), this, SLOT(createColleaguesForm()));
    connect(ui->btnSalary, SIGNAL(clicked()), this, SLOT(createSalaryForm()));
    connect(ui->btnOffice, SIGNAL(clicked()), this, SLOT(createOfficeForm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
