#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QIcon>
#include <QPushButton>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint | Qt::Window | Qt::CustomizeWindowHint),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);   
    setUpShadow();
    ui->lblIncorrectLogin->hide();

    mAnimationController = new AnimationController();

    connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->lblPictureCat, SIGNAL(inFocus()), this, SLOT(lostFocusOnLineEditsByClickOnPictures()));
    connect(ui->lblPictureNolt, SIGNAL(inFocus()), this,SLOT(lostFocusOnLineEditsByClickOnPictures()));

    connect(ui->txtLogin, SIGNAL(outFocus()), this, SLOT(lostFocusOnLineEditLogin()));
    connect(ui->txtPassword, SIGNAL(outFocus()), this, SLOT(lostFocusOnLineEditPassword()));    

    connect(ui->lblLogin, &LoginLabels::inFocus, this,[this]{setFocusOnLineEdit(ui->txtLogin);});
    connect(ui->lblPassword, &LoginLabels::inFocus, this,[this]{setFocusOnLineEdit(ui->txtPassword);});

    connect(ui->txtLogin, &LoginLineEdits::inFocus, this,[this]{doLabelAnimation(ui->lblLogin, 314);});
    connect(ui->txtPassword, &LoginLineEdits::inFocus, this,[this]{doLabelAnimation(ui->lblPassword, 360);});

    if(!QString(ui->txtLogin->text()).isEmpty())
    {
       ui->lblLogin->setGeometry(92, 314, 120, 13);       
    }
    if(!QString(ui->txtPassword->text()).isEmpty())
    {
       ui->lblPassword->setGeometry(92, 360, 120, 13);
    }    
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

bool LoginWindow::isMousePointerInFrame()
{
    return (mMouseClickXCoordinate >= mFrameStartPointX && mMouseClickXCoordinate <= mFrameWidth &&
            mMouseClickYCoordinate >= mFrameStartPointY && mMouseClickYCoordinate <= mFrameHeight);
}

void LoginWindow::clearFocusOfLineEdits()
{
    ui->txtLogin->clearFocus();
    ui->txtPassword->clearFocus();
}

void LoginWindow::setUpShadow()
{
    setAttribute(Qt::WA_TranslucentBackground);

    CustomShadowEffect  *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(5.0);
    bodyShadow->setDistance(1.0);
    bodyShadow->setColor(QColor(9,146,177));

    ui->lblPictureCat->setGraphicsEffect(bodyShadow);
}

void LoginWindow::login()
{
    QString inputLogin = ui->txtLogin->text();
    QString inputPassword = ui->txtPassword->text();

    if(inputLogin == mLogin && inputPassword == mPassword)
    {
        hide();
        mMainWindow = new MainWindow(this);
        mMainWindow->show();
    }
    else
    {
       ui->lblIncorrectLogin->show();
    }
}

void LoginWindow::setFocusOnLineEdit(QLineEdit *lineEdint)
{
    lineEdint->setFocus();
}

void LoginWindow::doLabelAnimation(QLabel *label, int y)
{
    mAnimationController->labelAnimationByY(label, mAnimationDuration, y);
    ui->lblIncorrectLogin->hide();    
}

void LoginWindow::lostFocusOnLineEditLogin()
{
    if(QString(ui->txtLogin->text()).isEmpty())
    {
       mAnimationController->labelAnimationByY(ui->lblLogin, mAnimationDuration, 332);
    }
}

void LoginWindow::lostFocusOnLineEditPassword()
{
    if(QString(ui->txtPassword->text()).isEmpty())
    {
       mAnimationController->labelAnimationByY(ui->lblPassword, mAnimationDuration, 378);
    }
}

void LoginWindow::lostFocusOnLineEditsByClickOnPictures()
{
    clearFocusOfLineEdits();
}

void LoginWindow::mousePressEvent(QMouseEvent *event)
{
    mMouseClickXCoordinate = event->x();
    mMouseClickYCoordinate = event->y();
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(isMousePointerInFrame())
    {
        clearFocusOfLineEdits();
        move(event->globalX()-mMouseClickXCoordinate,event->globalY()-mMouseClickYCoordinate);
    }
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *event)
{
   mMouseClickXCoordinate = 0;
   mMouseClickYCoordinate = 0;
}


