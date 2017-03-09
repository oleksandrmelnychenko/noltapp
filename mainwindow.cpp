#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::createColleaguesForm()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mCurrentMdiSubForm = new ColleaguesForm(ui->mdiArea);
    mCurrentMdiSubForm->setGeometry(10,40,640,440);
    mCurrentMdiSubForm->show();

}

void MainWindow::createOfficeForm()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mCurrentMdiSubForm = new OfficeForm(ui->mdiArea);
    mCurrentMdiSubForm->setGeometry(10,40,640,440);
    mCurrentMdiSubForm->show();
}

void MainWindow::createSalaryForm()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mCurrentMdiSubForm = new SalaryForm(ui->mdiArea);
    mCurrentMdiSubForm->setGeometry(10,40,640,440);
    mCurrentMdiSubForm->show();
}

void MainWindow::deleteMdiSubForm(QMdiSubWindow *form)
{
    if(form != nullptr)
    {
            delete mCurrentMdiSubForm;
            mCurrentMdiSubForm = nullptr;
            qDebug() << "Delete CurrentMdiSubForm";
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
