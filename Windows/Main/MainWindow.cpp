#include "MainWindow.h"
#include "ui_mainwindow.h"


void MainWindow::SetPressButtonStyleSheet(QPushButton *pressedButton, QPushButton *secondButton, QPushButton *thirdButton)
{
    pressedButton->setStyleSheet("color:#ffffff; background-color:transparent; border : none;");
    secondButton->setStyleSheet("color:#909090; background-color:transparent; border : none;");
    thirdButton->setStyleSheet("color:#909090; background-color:transparent; border : none;");
}

bool MainWindow::isMousePointerInFrame()
{
    return (mMouseClickXCoordinate >= mFrameStartPointX && mMouseClickXCoordinate <= mFrameWidth &&
            mMouseClickYCoordinate >= mFrameStartPointY && mMouseClickYCoordinate <= mFrameHeight);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mMouseClickXCoordinate = event->x();
    mMouseClickYCoordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(isMousePointerInFrame())
    {
        move(event->globalX()-mMouseClickXCoordinate,event->globalY()-mMouseClickYCoordinate);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mMouseClickXCoordinate = 0;
    mMouseClickYCoordinate = 0;
}

void MainWindow::createColleaguesView()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mCurrentMdiSubForm = new ColleaguesView(ui->mdiArea);    
    mCurrentMdiSubForm->show();
    connect(dynamic_cast<ColleaguesView*>(mCurrentMdiSubForm), SIGNAL(clickedNewLabel()),
            this, SLOT(createAddColeagueView()));
    connect(dynamic_cast<ColleaguesView*>(mCurrentMdiSubForm), SIGNAL(updateCurrentCollegues(long)),
            this, SLOT(createUpdateColleagueView(long)));    
    SetPressButtonStyleSheet(ui->btnColleagues,ui->btnOffice,ui->btnSalary);
}

void MainWindow::createAddColeagueView()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mCurrentMdiSubForm = new AddCollegueView(ui->mdiArea);
    mCurrentMdiSubForm->show();

    connect(dynamic_cast<AddCollegueView*>(mCurrentMdiSubForm), SIGNAL(requestStatus(QString)),
            this, SLOT(addColleagueRequestStatus(QString)));
}

void MainWindow::createUpdateColleagueView(long id)
{    
    mCurrentMdiSubForm->close();    
    mCurrentMdiSubForm = new UpdateCollegueView(ui->mdiArea,id);   
    mCurrentMdiSubForm->show();

    connect(dynamic_cast<UpdateCollegueView*>(mCurrentMdiSubForm), SIGNAL(requestStatus(QString)),
            this, SLOT(updateColleagueRequestStatus(QString)));

    qDebug() << id;
}

void MainWindow::createOfficeView()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mCurrentMdiSubForm = new OfficeView(ui->mdiArea);    
    mCurrentMdiSubForm->show();
    SetPressButtonStyleSheet(ui->btnOffice,ui->btnColleagues,ui->btnSalary);
}

void MainWindow::createSalaryView()
{
    deleteMdiSubForm(mCurrentMdiSubForm);
    mCurrentMdiSubForm = new SalaryView(ui->mdiArea);    
    mCurrentMdiSubForm->show();
    SetPressButtonStyleSheet(ui->btnSalary,ui->btnOffice,ui->btnColleagues);
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

void MainWindow::collapseMainWindow()
{
    QWidget::setWindowState(Qt::WindowMinimized);
}

void MainWindow::updateColleagueRequestStatus(const QString &status)
{
    ui->lblRequestStatus->setText(status);
    ui->lblRequestStatus->setGeometry(mlbRequestStatusForlUpdateColleagueXPosition,
                                      mlbRequestStatusForlUpdateColleagueYPosition,
                                      mlbRequestStatusForlUpdateColleagueWidth,
                                      mlbRequestStatusForlUpdateColleagueHeight);
    ui->lblRequestStatus->setVisible(true);
    QTimer::singleShot(1500,this,SLOT(setlblRequestStatusVisibleToFalse()));
}

void MainWindow::addColleagueRequestStatus(const QString &status)
{
    ui->lblRequestStatus->setText(status);
    ui->lblRequestStatus->setGeometry(mlblRequestStatusForAddColleagueXPosition,
                                      mlblRequestStatusForAddColleagueYPosition,
                                      mlblRequestStatusForAddColleagueWidth,
                                      mlblRequestStatusForAddColleagueHeight);

    ui->lblRequestStatus->setVisible(true);
    QTimer::singleShot(1500,this,SLOT(setlblRequestStatusVisibleToFalse()));
}

void MainWindow::setlblRequestStatusVisibleToFalse()
{
    ui->lblRequestStatus->setVisible(false);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint | Qt::Window | Qt::CustomizeWindowHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btbReqtangle->setEnabled(false);
    ui->lblRequestStatus->setVisible(false);

    createColleaguesView();

    connect(ui->btnColleagues, SIGNAL(clicked()), this, SLOT(createColleaguesView()));
    connect(ui->btnSalary, SIGNAL(clicked()), this, SLOT(createSalaryView()));
    connect(ui->btnOffice, SIGNAL(clicked()), this, SLOT(createOfficeView()));
    connect(ui->btnQuit, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btnCollapse, SIGNAL(clicked(bool)), this, SLOT(collapseMainWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
