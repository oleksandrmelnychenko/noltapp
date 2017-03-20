#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QIcon>
#include <QPushButton>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint | Qt::Window | Qt::CustomizeWindowHint),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    mAnimationController = new LoginController();

    connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->lblLogin, SIGNAL(inFocus()), this, SLOT(doLabelLoginAnimation()));
    connect(ui->lblPassword, SIGNAL(inFocus()), this, SLOT(doLabelPasswordAnimation()));
    connect(ui->lblPictureCat, SIGNAL(inFocus()), this, SLOT(lostFocusOnLineEditsByClickOnPictures()));
    connect(ui->lblPictureNolt, SIGNAL(inFocus()), this, SLOT(lostFocusOnLineEditsByClickOnPictures()));

    connect(ui->txtLogin, SIGNAL(inFocus()), this, SLOT(doLabelLoginAnimation()));
    connect(ui->txtLogin, SIGNAL(outFocus()), this, SLOT(lostFocusOnLineEdits()));
    connect(ui->txtPassword, SIGNAL(inFocus()), this, SLOT(doLabelPasswordAnimation()));
    connect(ui->txtPassword, SIGNAL(outFocus()), this, SLOT(lostFocusOnLineEdits()));

    ui->lblIncorrectLogin->hide();

    if(!QString(ui->txtLogin->text()).isEmpty())
    {
       ui->lblLogin->setGeometry(92, 314, 120, 13);
    }
    if(!QString(ui->txtPassword->text()).isEmpty())
    {
       ui->lblPassword->setGeometry(92, 360, 120, 13);
    }

    setAttribute(Qt::WA_TranslucentBackground);

    CustomShadowEffect  *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(35.0);
    bodyShadow->setDistance(5.0);
    bodyShadow->setColor(QColor(9,146,177));    
    ui->lblPictureCat->setGraphicsEffect(bodyShadow);    
}

LoginWindow::~LoginWindow()
{
    delete ui;
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

void LoginWindow::doLabelLoginAnimation()
{
    mAnimationController->labelAnimation(ui->lblLogin, 250, 92, 314, 120, 13 );
    ui->lblIncorrectLogin->hide();
    ui->txtLogin->setFocus();
}

void LoginWindow::doLabelPasswordAnimation()
{
    mAnimationController->labelAnimation(ui->lblPassword, 250, 92, 360, 120, 13 );
    ui->lblIncorrectLogin->hide();
    ui->txtPassword->setFocus();
}

void LoginWindow::lostFocusOnLineEdits()
{
    if(QString(ui->txtLogin->text()).isEmpty())
    {
       mAnimationController->labelAnimation(ui->lblLogin, 250, 92, 332, 120, 13);
    }
    if(QString(ui->txtPassword->text()).isEmpty())
    {
       mAnimationController->labelAnimation(ui->lblPassword, 250, 92, 378, 120, 13);
    }
}

void LoginWindow::lostFocusOnLineEditsByClickOnPictures()
{
    if(QString(ui->txtLogin->text()).isEmpty())
    {
       mAnimationController->labelAnimation(ui->lblLogin, 250, 92, 332, 120, 13);
    }
    if(QString(ui->txtPassword->text()).isEmpty())
    {
       mAnimationController->labelAnimation(ui->lblPassword, 250, 92, 378, 120, 13);
    }
    ui->txtLogin->clearFocus();
    ui->txtPassword->clearFocus();
}

void LoginWindow::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();    
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_nMouseClick_X_Coordinate >= 5 && m_nMouseClick_X_Coordinate <= 498 &&
            m_nMouseClick_Y_Coordinate >= 5 && m_nMouseClick_Y_Coordinate <= 21)
    {
        move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    }
}


