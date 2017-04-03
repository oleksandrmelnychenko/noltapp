#include "MainWindow.h"
#include "ui_mainwindow.h"

void MainWindow::createColleaguesView()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mCurrentMdiSubForm = new ColleaguesView(ui->mdiArea);
    mCurrentMdiSubForm->setGeometry(10,40,1330,600);
    mCurrentMdiSubForm->show();
    connect(dynamic_cast<ColleaguesView*>(mCurrentMdiSubForm), SIGNAL(clickedAddCollegueButton()), this, SLOT(createAddColegueView()));
}

void MainWindow::createAddColegueView()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mCurrentMdiSubForm = new AddCollegueView(ui->mdiArea);
    mCurrentMdiSubForm->setGeometry(10,40,1330,600);
    mCurrentMdiSubForm->show();
}

void MainWindow::createOfficeView()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mCurrentMdiSubForm = new OfficeView(ui->mdiArea);
    mCurrentMdiSubForm->setGeometry(10,40,1330,600);
    mCurrentMdiSubForm->show();
}

void MainWindow::createSalaryView()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mCurrentMdiSubForm = new SalaryView(ui->mdiArea);
    mCurrentMdiSubForm->setGeometry(10,40,1330,600);
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

    createColleaguesView();
    mCurrentMdiSubForm->setGeometry(0,0,640,440);

    connect(ui->btnColleagues, SIGNAL(clicked()), this, SLOT(createColleaguesView()));
    connect(ui->btnSalary, SIGNAL(clicked()), this, SLOT(createSalaryView()));
    connect(ui->btnOffice, SIGNAL(clicked()), this, SLOT(createOfficeView()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
