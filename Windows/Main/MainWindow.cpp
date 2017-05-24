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

void MainWindow::setUpShadow()
{
    setAttribute(Qt::WA_TranslucentBackground);

    CustomShadowEffect  *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(5.0);
    bodyShadow->setDistance(1.0);
    bodyShadow->setColor(QColor(9,146,177));

    ui->lblBackGroundPicture->setGraphicsEffect(bodyShadow);
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
            this, SLOT(AddColleagueRequestStatus(QString)));
    connect(dynamic_cast<AddCollegueView*>(mCurrentMdiSubForm), SIGNAL(clickColleaguelbl()),
            this, SLOT(createColleaguesView()));
}

void MainWindow::createUpdateColleagueView(long id)
{    
    mCurrentMdiSubForm->close();
    mCurrentMdiSubForm = nullptr; // mb help
    mCurrentMdiSubForm = new UpdateCollegueView(ui->mdiArea,id);   
    mCurrentMdiSubForm->show();

    connect(dynamic_cast<UpdateCollegueView*>(mCurrentMdiSubForm), SIGNAL(updateColleagueRequestStatus(QString)),
            this, SLOT(UpdateColleagueRequestStatus(QString)));

    connect(dynamic_cast<UpdateCollegueView*>(mCurrentMdiSubForm), SIGNAL(clickColleaguelbl()),
            this, SLOT(createColleaguesView()));

    connect(dynamic_cast<UpdateCollegueView*>(mCurrentMdiSubForm), SIGNAL(deleteColleagueRequestStatus(QString)),
            this, SLOT(UpdateColleagueDeleteRequestStatus(QString)));
    connect(dynamic_cast<UpdateCollegueView*>(mCurrentMdiSubForm), SIGNAL(clickDeletelbl()),
            this, SLOT(createColleaguesView()));
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

    connect(dynamic_cast<SalaryView*>(mCurrentMdiSubForm), SIGNAL(paidSalaryRequestStatus(QString)),
            this, SLOT(DoPaymentStatus(QString)));
    connect(dynamic_cast<SalaryView*>(mCurrentMdiSubForm), SIGNAL(updateColleagueSalaryRequestStatus(QString)),
            this, SLOT(UpdateSalaryStatus(QString)));
}

void MainWindow::deleteMdiSubForm(QMdiSubWindow *form)
{
    if(form != nullptr)
    {
        delete mCurrentMdiSubForm;
        mCurrentMdiSubForm = nullptr;
    }
}

void MainWindow::collapseMainWindow()
{
    QWidget::setWindowState(Qt::WindowMinimized);
}

void MainWindow::UpdateColleagueRequestStatus(const QString &status)
{
    ui->lblRequestStatus->setText(status);
    ui->lblRequestStatus->setGeometry(mlbRequestStatusForlUpdateColleagueXPosition,
                                      mlbRequestStatusYPosition,
                                      mlbRequestStatusForlUpdateColleagueWidth,
                                      mlbRequestStatusHeight);
    ui->lblRequestStatus->setVisible(true);
    QTimer::singleShot(1500,this,SLOT(setlblRequestStatusVisibleToFalse()));
}

void MainWindow::UpdateColleagueDeleteRequestStatus(const QString &status)
{
    ui->lblRequestStatus->setText(status);
    ui->lblRequestStatus->setGeometry(mlblRequestStatusForDeleteColleagueXPosition,
                                      mlbRequestStatusYPosition,
                                      mlblRequestStatusForDeleteColleagueWidth,
                                      mlbRequestStatusHeight);
    ui->lblRequestStatus->setVisible(true);
    QTimer::singleShot(1500,this,SLOT(setlblRequestStatusVisibleToFalse()));
}

void MainWindow::AddColleagueRequestStatus(const QString &status)
{
    ui->lblRequestStatus->setText(status);
    ui->lblRequestStatus->setGeometry(mlblRequestStatusForAddColleagueXPosition,
                                      mlbRequestStatusYPosition,
                                      mlblRequestStatusForAddColleagueWidth,
                                      mlbRequestStatusHeight);

    ui->lblRequestStatus->setVisible(true);
    QTimer::singleShot(1500,this,SLOT(setlblRequestStatusVisibleToFalse()));
}

void MainWindow::UpdateSalaryStatus(const QString &status)
{
    ui->lblRequestStatus->setText(status);

    ui->lblRequestStatus->setGeometry(mlblRequestStatusForUpdateSalaryXPosition,
                                      mlbRequestStatusYPosition,
                                      mlblRequestStatusForUpdateSalaryWidth,
                                      mlbRequestStatusHeight);

    ui->lblRequestStatus->setVisible(true);
    QTimer::singleShot(1500,this,SLOT(setlblRequestStatusVisibleToFalse()));
}

void MainWindow::DoPaymentStatus(const QString &status)
{
    ui->lblRequestStatus->setText(status);

    ui->lblRequestStatus->setGeometry(mlblRequestStatusForDoPaymentXPosition,
                                      mlbRequestStatusYPosition,
                                      mlblRequestStatusForDoPaymentWidth,
                                      mlbRequestStatusHeight);

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

    setUpShadow();

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
